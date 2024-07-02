#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <thread>
#include <vector>
#include <cstdlib>
#include <random>

using namespace std;
using namespace std::chrono;

int envInt(const char* name, int defaultValue) {
	auto s = getenv(name);
	if (s != nullptr) return atoi(s);
	return defaultValue;
}

std::string envStr(const char* name, const char* defaultValue) {
	auto s = getenv(name);
	if (s != nullptr) return s;
	return "";
}

using Int = long long;
const Int dx[] = {-1, 0,  1, -1, 0, 1, -1, 0, 1};
const Int dy[] = {-1, -1,  -1, 0, 0, 0, 1, 1, 1};
using StageData = vector<pair<Int, Int>>;

struct State {
    Int vx, vy, px, py;
    bool operator < (const State &rhs) const {
        if(vx != rhs.vx) return vx < rhs.vx;
        if(vy != rhs.vy) return vy < rhs.vy;
        if(px != rhs.px) return px < rhs.px;
        return py < rhs.py;
    }
};

StageData input(istream& is){
	StageData vg;
    int x, y;
	string s;
	while(getline(is, s)) {
		if (s[0] == '#') continue;
		stringstream ss(s);
		ss >> x >> y;
        vg.push_back(make_pair(x, y));
	}
    return vg;
}

Int gcd(Int a, Int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

double abs(pair<Int, Int> a) {
	// return max(abs(a.first), abs(a.second));
	return sqrt(a.first * a.first + a.second * a.second);
}

template <typename T> class Ranking {
public:
	bool is_rankin(const T& value) {
		return m_.size() < n ? true : min_element() < value;
	}

	void push(const T& value) {
		m_.insert(value);
		if (size() == n + 1) {
			pop_min();
		}
	}

	T min_element() {
		assert(!empty());
		return *m_.begin();
	}

	const T& min_element() const {
		assert(!empty());
		return *m_.begin();
	}

	T max_element() {
		assert(!empty());
		return *m_.rbegin();
	}

	const T& max_element() const {
		assert(!empty());
		return *m_.rbegin();
	}

	void pop_min() {
		assert(!empty());
		m_.erase(m_.begin());
	}

	void pop_max() {
		assert(!empty());
		m_.erase(--m_.end());
	}

	[[nodiscard]] bool empty() const { return m_.empty(); }

	[[nodiscard]] size_t size() const { return m_.size(); }

	void clear() { m_.clear(); }

	[[nodiscard]] const std::multiset<T>& data() const { return m_; }

private:
	int n = envInt("WIDTH", 1000);
	std::multiset<T> m_;
};

class ChokudaiSearch {
public:
	struct DirListNode {
		uint8_t dir;
		std::shared_ptr<DirListNode> parent;

		DirListNode() : dir(0), parent(nullptr) {}
		DirListNode(const int dir, std::shared_ptr<DirListNode> parent)
			: dir(dir), parent(std::move(parent)) {}
	};

	struct SearchNode {
		int next_index{};
		double score{};
		Int px{}, py{};
		Int vx{}, vy{};
		std::shared_ptr<DirListNode> dir_list;
		bool operator<(const SearchNode& o) const { return score < o.score; }
	};

	ChokudaiSearch(const ChokudaiSearch&) = delete;
	ChokudaiSearch(ChokudaiSearch&&) = delete;
	ChokudaiSearch& operator=(const ChokudaiSearch&) = delete;
	ChokudaiSearch() = delete;

	explicit ChokudaiSearch(StageData stage_data, bool auto_target)
		: stage_data_(std::move(stage_data)) {
		int maxTurn = envInt("MAXTURN", 1000);
		ranking_.resize(maxTurn+ 1);
		bests_.resize(maxTurn);

		mutex_.resize(maxTurn + 1);
		for (auto& m : mutex_) {
			m = std::make_unique<std::mutex>();
		}

		SearchNode node;
		node.next_index = 0;
		node.score = 0;
		node.px = 0;
		node.py = 0;
		node.vx = 0;
		node.vy = 0;

		while (stage_data_[node.next_index].first == node.px && stage_data_[node.next_index].second == node.py) {
			node.next_index++;
		}
		ranking_[0].push(node);
	}

	std::vector<SearchNode> GetBests() const {
		std::vector<SearchNode> ret;
		for (const auto& best : bests_) {
			if (0 < best.next_index) {
				ret.push_back(best);
			}
		}
		return ret;
	}

	void Run(int target_depth, int timeout_ms = 2000) {
		auto f = [this, target_depth, timeout_ms]() {
			const auto t0 = high_resolution_clock::now();
			while (true) {
				const auto updated = RunInternal(target_depth, 20);
				if (!updated) {
					break;
				}

				const auto t1 = high_resolution_clock::now();
				const auto ms = duration_cast<milliseconds>(t1 - t0).count();
				if (timeout_ms < ms) {
					break;
				}
			}
		};

		// const auto n_thread = std::max(std::thread::hardware_concurrency(), 1u);
		const auto n_thread = 1;
		std::vector<std::thread> threads;
		threads.reserve(n_thread);
		for (int i = 0; i < n_thread; i++) {
			threads.emplace_back(f);
		}
		for (int i = 0; i < n_thread; i++) {
			threads[i].join();
		}
	}

private:
	bool RunInternal(int target_depth, int loop_count) {
		SearchNode node, tmp_node;
		bool updated = true;

		for (int loop = 0; updated && loop < loop_count; ++loop) {
			updated = false;

			for (int depth = 0; depth < target_depth; ++depth) {
				if (base_turn_ + depth == bests_.size()) {
					break;
				}

				{
					std::lock_guard lock(*mutex_[depth]);
					auto& prev = ranking_[depth];
					if (prev.empty()) {
						continue;
					}

					node = prev.max_element();
					prev.pop_max();
					if (node.next_index == stage_data_.size()) {
						continue;
					}

					const auto h = Hash(node.px, node.px, node.vx, node.vy, node.next_index);
					const auto h2 = static_cast<uint16_t>(h ^ h >> 16 ^ h >> 32 ^ h >> 48);
					{
						std::lock_guard g_lock(g_mutex_);
						auto &hash_pool = weak_hash_;
						if (hash_pool[h2] == h) {
							continue;
						}
						hash_pool[h2] = h;
					}
					updated = true;
				}

				for (int dir = 0; dir < 9; dir++) {
					const auto [npx, npy, nvx, nvy, nni] = Step(node.px, node.py, node.vx, node.vy, node.next_index, dir);

					{
						std::lock_guard lock(*mutex_[depth]);
						auto& best = bests_[depth];
						if (best.next_index < nni) {
							// if (depth + 1 == bests_.size()) { cerr << "nni:" << nni << endl; }
							best.next_index = nni;
							best.px = npx;
							best.py = npy;
							best.vx = nvx;
							best.vy = nvy;
							best.dir_list = std::make_shared<DirListNode>(dir, node.dir_list);
						}
					}

					tmp_node.score = EvalFunc(npx, npy, nvx, nvy, nni);
					{
						std::lock_guard lock(*mutex_[depth + 1]);
						if (ranking_[depth + 1].is_rankin(tmp_node)) {
							tmp_node.next_index = nni;
							tmp_node.px = npx;
							tmp_node.py = npy;
							tmp_node.vx = nvx;
							tmp_node.vy = nvy;
							tmp_node.dir_list = std::make_shared<DirListNode>(dir, node.dir_list);
							ranking_[depth + 1].push(tmp_node);
						}
					}
				}
			}
		}

		return updated;
	}

	[[nodiscard]] std::tuple<Int, Int, Int, Int, int> Step(Int px, Int py, Int vx, Int vy, int next_index, int dir) const {
		vx += dx[dir];
		vy += dy[dir];
		px += vx;
		py += vy;
		while (stage_data_[next_index].first == px && stage_data_[next_index].second == py) {
			next_index++;
		}
		return {px, py, vx, vy, next_index};
	}

	[[nodiscard]] double EvalFunc(Int px, Int py, Int vx, Int vy, int next_index) const {
		const auto tp = stage_data_[next_index];
		const auto sp = next_index == 0 ? make_pair<Int, Int>(0, 0) : stage_data_[next_index - 1];
		const double w1 = abs(make_pair<Int, Int>(tp.first - px - vx, tp.second - py - vy));
		const double w2 = abs(make_pair<Int, Int>(tp.first - sp.first, tp.second - sp.second));
		return 1000.0 * (next_index + (1.0 - w1/w2));
	}

	static uint64_t Hash(Int px, Int py, Int vx, Int vy, int next_index) {
		uint64_t ret = 37;
		ret = ret * 573292817ULL + next_index;
		ret = ret * 573292817ULL + px;
		ret = ret * 573292817ULL + py;
		ret = ret * 573292817ULL + vx;
		ret = ret * 573292817ULL + vy;
		return ret;
	}
	int base_turn_ = 0;
	StageData stage_data_;
	std::array<uint64_t, 1 << 16> weak_hash_;
	std::vector<SearchNode> bests_;
	std::vector<Ranking<SearchNode>> ranking_;
	std::vector<std::unique_ptr<std::mutex>> mutex_;
	std::mutex g_mutex_;
};


class PathFinder {
	// やりたいこと
	// クエリ1: p0, v0 から p1 に移動するときの v1の候補を返却する
	//   探索時に使用する.
	// クエリ2: p0, v0 から p1, v1 に移動する a の配列を返却する
	//   経路復元時に使用する.

	static const int T = 150;
	static const int X = 10000;
public:
	// テーブル生成
	// dp[t][x] = set(v)
	// 1ターン後にxに到達する時のv (存在しない場合は空)
	void BuildTable() {
		dp.resize(T);
		for (int t = 0; t < T; t++) {
			dp[t].resize(X);
		}

		dp[0][0].emplace(0);
		for (int t = 0; t < dp.size() - 1; t++) {
			for (int x = 0; x < dp[t].size(); x++) {
				for (auto v: dp[t][x]) {
					if (v != 0 && 0 <= x + v && x + v < X) {
						dp[t + 1][x + v].emplace(v);
					}

					if (0 <= x + v + 1 && x + v + 1 < X) {
						dp[t + 1][x + v + 1].emplace(v + 1);
					}

					if (0 <= x + v - 1 && x + v - 1 < X) {
						dp[t + 1][x + v - 1].emplace(v - 1);
					}
				}
			}
		}
	}

	// 1次元 移動可能判定
	// 初期状態: t, x, v = 0, 0, 0
	// 終了状態: t, x, v = t, x, v
	bool CanMove1d(int t, int x, int v) const {
		if (t == 0) {
			if (x == 0 && v == 0) return true;
			return false;
		}

		if (x < 0) {
			x *= -1;
			v *= -1;
		}

		return dp[t][x].find(v) != dp[t][x].end();
	}

	// 1次元 到達時の速度の列を返す
	// 初期状態: t, x, v = 0, x0, v0
	// 終了状態: t, x, v = t, x1, v1
	// v1の配列を返す
	vector<int> GetVel1d(int t, int x0, int v0, int x1) const {
		int x = x1 - (x0 + v0 * t);
		bool minus = x < 0;
		if (minus) {
			x *= -1;
			v0 *= -1; // ??
		}

		auto vs = vector(dp[t][x].begin(), dp[t][x].end());
		if (minus) {
			for (auto &v: vs) {
				v *= -1;
			}
		}

		return vs;
	}

	// 1次元 加速度の列を返す
	// 初期状態: t, x, v = 0, 0, 0
	// 終了状態: t, x, v = t, x, v
	vector<char> GetAcc1d(int t, int x, int v) const {
		cerr << "Query; x, t, v = " << x << " " << t << " " << v << " " << endl;
		if (t == 0) {
			if (x == 0 && v == 0) return {0};
			return {};
		}

		bool minus = x < 0;
		if (minus) {
			x *= -1;
			v *= -1;
		}

		if (dp[t][x].find(v) == dp[t][x].end()) {
			return {};
		}

		vector<char> moves;

		while (t--) {
			int aa = -1;
			int xx = -1;

			for (int a = -1; a <= 1; a++) {
				xx = x - v;
				// cerr << "xx=" << xx << " a=" << a << " v-a=" << v-a << endl;
				if (0 <= xx && xx < X) {
					if (dp[t][xx].find(v - a) != dp[t][xx].end()) {
						// cerr << "found: a=" << a << " v=" << v - a << endl;
						aa = a;
						break;
					}
				}
			}

			if (xx == -1) {
				cerr << "not found" << endl;
				throw 1;
			}

			moves.emplace_back(minus ? -aa : aa);
			x = xx;
			v -= aa;
		}

		reverse(moves.begin(), moves.end());
		cerr << "Ans: "; for (auto c: moves) { cerr << int(c) << " "; } cerr << endl;
		return moves;
	}

	void LookTable(int x) {
		if (!(0 <= x && x < dp.size())) return;

		for (int t = 0; t < dp.size(); t++) {
			for (auto v: dp[t][x]) {
				cerr << "x, t, v = " << x << " " << t << " " << v << " " << endl;
			}
		}
	}

	void Test1d(int t, int prev_x, int prev_v, int new_x, int new_v) {
		int x = prev_x;
		int v = prev_v;

		auto moves = GetAcc1d(t, new_x, new_v);
		if (!moves.empty()) {
			for (auto a: moves) {
				v += a;
				x += v;
			}
			assert(x == new_x);
			assert(v == new_v);
		}
	}

private:
	// table[t][x] = v;
	vector<vector<set<int> > > dp;
};

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "need problem file path" << endl;
        exit(1);
    }

	PathFinder pf;

	pf.BuildTable();
	pf.LookTable(1);
	// pf.LookTable(2);

	pf.GetAcc1d(1, 1, 1);
	pf.GetAcc1d(2, 2, 1);
	pf.Test1d(1, 0, 0, 1, 1);
	pf.Test1d(10, 0, 0, 10, 0);
	pf.Test1d(10, 0, 0, -10, 0);
	pf.Test1d(10, 0, 0, 10, 2);
	pf.Test1d(10, 0, 0, 0, -2);

	exit(0);

    ifstream ifs(argv[1]);
    auto vg = input(ifs);
    ifs.close();
    cerr << "vg.size()=" << vg.size() << endl;

    ChokudaiSearch cs(vg, envInt("AUTO", 0));
    cs.Run(envInt("MAXTURN", 1000), envInt("TIMEOUT", 1000));
    auto bests = cs.GetBests();
    vector<int> moves;
    for (const auto &best: bests) {
	    if (best.next_index == vg.size()) {
		    for (auto ptr = best.dir_list; ptr != nullptr; ptr = ptr->parent) {
			    moves.push_back(ptr->dir + 1);
		    }
		    break;
	    }
    }

    if (!moves.empty()) {
	    cerr << "score: " << moves.size() << endl;
	    reverse(moves.begin(), moves.end());
	    for (auto dir: moves) {
		    cout << dir;
	    }
	    cout << endl;
    } else {
	    cerr << "Not found" << endl;
	    if (!bests.empty()) {
		    auto &best = bests.back();
		    cerr << "next_index=" << best.next_index << " score=" << best.score << endl;
		    for (auto ptr = best.dir_list; ptr != nullptr; ptr = ptr->parent) {
			    moves.push_back(ptr->dir + 1);
		    }
		    reverse(moves.begin(), moves.end());
		    for (auto dir: moves) {
			    cerr << dir;
		    }
		    cerr << endl;
	    }
    }
}
