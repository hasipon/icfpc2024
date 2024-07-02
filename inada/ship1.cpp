#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <thread>
#include <vector>

#define DUMPV(v) { cerr << #v << "="; for (const auto& e: (v)) { cerr << e << " "; } cerr << endl; }
#define DUMP(a) { cerr << #a << "=" << (a) << endl; }
#define mm_assert(cond) if (!(cond)) { std::cerr << "assertion failed: " << #cond << endl; throw 1; }
#define mm_assert2(cond, eval_) if (!(cond)) { std::cerr << "assertion failed: " << #cond << endl; {eval_;} throw 1; }

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
		shared_ptr<DirListNode> dir_list;
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


class MoveDatabse {
	// やりたいこと
	// クエリ1: p0, v0 から p1 に移動するときの v1の候補を返却する
	//   探索時に使用する.
	// クエリ2: p0, v0 から p1, v1 に移動する a の配列を返却する
	//   経路復元時に使用する.

public:
	static const int T = 100;
	static const int X = T * (T + 1) / 2;

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
					if (0 <= x + v && x + v < X) {
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

	// クエリ1: p0, v0 から p1 に移動するときの v1の候補を返却する
	vector<tuple<int, int, int> > VelCandidates(int x0, int y0, int vx0, int vy0, int x1, int y1) const {
		vector<tuple<int, int, int> > candidates; // t, vx, vy
		set<tuple<int, int> > used;

		const int max_xy = max(abs(x1 - x0), abs(y1 - y0));
		// const int t0 = max_xy * (max_xy + 1) / 2;
		int max_t = T;
		for (int t = 0; t < max_t ; t++) {
			auto vxs = GetVel1d(t, x0, vx0, x1);
			if (vxs.empty()) continue;

			auto vys = GetVel1d(t, y0, vy0, y1);
			if (vys.empty()) continue;

			if (max_t == T) {
				max_t = t + 3;
			}

			for (auto vx: vxs) {
				for (auto vy: vys) {
					if (used.find({vx, vy}) == used.end()) {
						candidates.emplace_back(t, vx, vy);
						used.emplace(vx, vy);
					}
				}
			}
		}

		return candidates;
	}

	// クエリ2: p0, v0 から p1, v1 に移動するコマンド列を返却する
	string GetCommands(
		int t,
		int x0, int y0, int vx0, int vy0,
		int x1, int y1, int vx1, int vy1) const {
		mm_assert2(0 <= t && t < T, DUMP(t));
		auto xa = GetAcc1d(t, x0, vx0, x1, vx1);
		auto ya = GetAcc1d(t, y0, vy0, y1, vy1);
		mm_assert(!xa.empty());
		mm_assert(!ya.empty());
		vector<char> ops;
		for (int i = 0; i < t; i++) {
			if (ya[i] == 1) ops.emplace_back('8' + xa[i]);
			if (ya[i] == 0) ops.emplace_back('5' + xa[i]);
			if (ya[i] == -1) ops.emplace_back('2' + xa[i]);
		}
		return {ops.begin(), ops.end()};
	}


	// 2次元 移動可能判定
	// 初期状態: t, x, y, vx, vy = x0, y0, vx0, vy0
	// 終了状態: t, x, y, vx, vy = x1, y1, vx1, vy1
	bool CanMove2d(
		int t,
		int x0, int y0, int vx0, int vy0,
		int x1, int y1, int vx1, int vy1) const {
		return CanMove1d(t, x0, vx0, x1, vx1) &&
		       CanMove1d(t, y0, vy0, y1, vy1);
	}

	// 1次元 移動可能判定
	// 初期状態: t, x, v = 0, x0, v0
	// 終了状態: t, x, v = t, x1, v1
	bool CanMove1d(int t, int x0, int v0, int x1, int v1) const {
		return CanMove1d(t, x1 - x0, v1 - v0);
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
		}

		mm_assert2(t < T, DUMP(t));
		mm_assert2(x < X, DUMP(x));
		auto vs = vector(dp[t][x].begin(), dp[t][x].end());
		if (minus) {
			for (auto &v: vs) {
				v *= -1;
			}
		}

		for (auto &v: vs) {
			v += v0;
		}

		return vs;
	}

	// 1次元 加速度の列を返す
	// 初期状態: t, x, v = 0, x0, v0
	// 終了状態: t, x, v = t, x1, v1
	vector<char> GetAcc1d(int t, int x0, int v0, int x1, int v1) const {
		return GetAcc1d(t, x1 - (x0 + v0 * t), v1 - v0);
	}

	// 1次元 加速度の列を返す
	// 初期状態: t, x, v = 0, 0, 0
	// 終了状態: t, x, v = t, x, v
	vector<char> GetAcc1d(int t, int x, int v) const {
		mm_assert(0 <= t && t < T);
		// cerr << "Query; t, x, v = " << t << " " << x << " " << v << " " << endl;
		if (t == 0) {
			if (x == 0 && v == 0) return {0};
			return {};
		}

		bool minus = x < 0;
		if (minus) {
			x *= -1;
			v *= -1;
		}

		mm_assert(x < X);
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

			mm_assert(xx != -1);
			moves.emplace_back(minus ? -aa : aa);
			x = xx;
			v -= aa;
		}

		reverse(moves.begin(), moves.end());
		// cerr << "Ans: "; for (auto c: moves) { cerr << int(c) << " "; } cerr << endl;
		return moves;
	}

	void LookTable(int x) {
		for (int t = 0; t < dp.size(); t++) {
			if (0 <= x && x < dp[t].size()) {
				for (auto v: dp[t][x]) {
					cerr << "x, t, v = " << x << " " << t << " " << v << " " << endl;
				}
			}
		}
	}

	void TestGetAcc1d() {
		auto test_cases = vector<tuple<int, int, int, int, int>> {
			{1, 0, 0, 1, 1},
			{10, 0, 0, 10, 0},
			{10, 0, 0, -10, 0},
			{10, 0, 0, 10, 2},
			{10, 0, 0, 0, -2},
		};

		for (const auto& [t, x0, v0, x1, v1] : test_cases) {
			auto moves = GetAcc1d(t, x1, v1);
			assert(!moves.empty());

			auto v = v0;
			auto x = x0;
			for (auto a: moves) {
				v += a;
				x += v;
			}

			assert(x == x1);
			assert(v == v1);
		}
	}

	void TestGetVel1d() {
		auto test_cases = vector<tuple<int, int, int, int, int>> {
			{1, 0, 0, 1, 1},
			{10, 0, 0, 55, 10},
			{10, 10, 0, 65, 10},
			{1, -1, 1, 0, 1},
			{1, 1, -1, 0, -1},
			{1, 1, -1, 1, 0},
		};

		for (const auto& [t, x0, v0, x1, v1] : test_cases) {
			auto vs = GetVel1d(t, x0, v0, x1);
			mm_assert(!vs.empty());
			cerr << "vs=";
			for (auto& v : vs) {
				cerr << v << " ";
			}
			cerr << endl;
			cerr << "v1=" << v1 << endl;
			mm_assert(find(vs.begin(), vs.end(), v1) != vs.end());
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

	MoveDatabse db;
	db.BuildTable();
	db.TestGetAcc1d();
	db.TestGetVel1d();

    ifstream ifs(argv[1]);
    auto vg = input(ifs);
    ifs.close();
    cerr << "vg.size()=" << vg.size() << endl;

	int t = 0;
	int x = 0;
	int y = 0;
	int vx = 0;
	int vy = 0;
	string cmds;
	for (int i = 0; i < vg.size(); i++) {
		auto debug = vector{x, y, vx, vy, (int)vg[i].first, (int)vg[i].second};
		DUMPV(debug);
		auto candidates = db.VelCandidates(x, y, vx, vy, vg[i].first, vg[i].second);
		mm_assert(!candidates.empty());
		auto [dt, vx1, vy1] = candidates[0];
		cerr << i+1 << "/" << vg.size() << " candidate dt, vx1, vy1 = " << dt << " " << vx1 << " " << vy1 << endl;
		cmds += db.GetCommands(dt, x, y, vx, vy, vg[i].first, vg[i].second, vx1, vy1);
		cerr << "GetCommands ok" << endl;
		t += dt;
		x = vg[i].first;
		y = vg[i].second;
		vx = vx1;
		vy = vy1;
		// cerr << cmds << endl;
	}
	cout << cmds << endl;

	// TODO
	exit(0);

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
