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
    while(is >> x >> y){
        vg.push_back(make_pair(x, y));
    }
    return vg;
}

Int gcd(Int a, Int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}

double abs(pair<Int, Int> a) {
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
		int next_index;
		double score;
		Int px, py;
		Int vx, vy;
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
		weak_hash_.resize(maxTurn);
		mutex_.resize(maxTurn + 1);
		for (auto& m : mutex_) {
			m = std::make_unique<std::mutex>();
		}

		auto_target_sort_= auto_target;
		if (auto_target_sort_) {
			std::lock_guard lock(g_mutex_);
			fixed_target_index_ = 0;
			sort(stage_data_.begin(), stage_data_.end(), [](auto& a, auto& b) {
				return abs(a) < abs(b);
			});
		}

		SearchNode node;
		node.next_index = 0;
		node.score = 0;
		node.px = 0;
		node.py = 0;
		node.vx = 0;
		node.vy = 0;
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

		const auto n_thread = std::max(std::thread::hardware_concurrency(), 1u);
		// const auto n_thread = 1;
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
					auto& hash_pool = weak_hash_[depth];
					if (hash_pool[h2] == h) {
						continue;
					}
					hash_pool[h2] = h;
					updated = true;
				}

				for (int dir = 0; dir < 9; dir++) {
					const auto [npx, npy, nvx, nvy, nni] = Step(node.px, node.py, node.vx, node.vy, node.next_index, dir);

					{
						std::lock_guard lock(*mutex_[depth]);
						auto& best = bests_[depth];
						if (best.next_index < nni) {
							best.next_index = nni;
							best.px = npx;
							best.py = npy;
							best.vx = nvx;
							best.vy = nvy;
							best.dir_list = std::make_shared<DirListNode>(dir, node.dir_list);
						}
					}

					if (auto_target_sort_ && nni != node.next_index) {
						std::lock_guard g_lock(g_mutex_);
						if (fixed_target_index_ < nni) {
							fixed_target_index_ = nni;
							sort(stage_data_.begin() + fixed_target_index_, stage_data_.end(), [&](auto &a, auto &b) {
								auto aa = make_pair<Int, Int>(a.first - node.px - node.vx, a.second - node.py - node.vy);
								auto bb = make_pair<Int, Int>(b.first - node.px - node.vx, b.second - node.py - node.vy);
								return abs(aa) < abs(bb);
							});
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

		/*
		if (vx != 0 && vy != 0) {
			const auto num_p = gcd(abs(vx), abs(vy));
			for (int dt = 0; dt < num_p; dt++) {
				const auto xx = px + vx * dt / num_p;
				const auto yy = py + vy * dt / num_p;
				while (stage_data_[next_index].first == xx && stage_data_[next_index].second == yy) {
					next_index++;
				}
			}
		}

		if (vx != 0 && vy == 0) {
			const auto num_p = abs(vx);
			for (int dt = 0; dt < num_p; dt++) {
				const auto xx = px + vx * dt / num_p;
				const auto yy = py;
				while (stage_data_[next_index].first == xx && stage_data_[next_index].second == yy) {
					next_index++;
				}
			}
		}

		if (vx == 0 && vy != 0) {
			const auto num_p = abs(vy);
			for (int dt = 0; dt < num_p; dt++) {
				const auto xx = px;
				const auto yy = py + vy * dt / num_p;
				while (stage_data_[next_index].first == xx && stage_data_[next_index].second == yy) {
					next_index++;
				}
			}
		}
		*/

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
		const auto w1 = abs(make_pair<Int, Int>(tp.first - px - vx, tp.second - py - vy));
		const auto w2 = abs(make_pair<Int, Int>(tp.first - sp.first, tp.second - sp.second));
		return 1000.0 * (next_index + (1.0 - w1/w2));
		// return 10000.0 * next_index - w1;
		// return 1000.0 * next_index;
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
	bool auto_target_sort_ = false;
	int fixed_target_index_  = 0;
	StageData stage_data_;
	std::vector<std::array<uint64_t, 1 << 16>> weak_hash_;
	std::vector<SearchNode> bests_;
	std::vector<Ranking<SearchNode>> ranking_;
	std::vector<std::unique_ptr<std::mutex>> mutex_;
	std::mutex g_mutex_;
};

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "need problem file path" << endl;
        exit(1);
    }

    ifstream ifs(argv[1]);
    auto vg = input(ifs);
    ifs.close();

	auto sol_file = envStr("TSP_SOL", "");
    if (!sol_file.empty()) {
	    ifstream fs(sol_file);
    	if (fs.is_open()) {
		    int n, k;
		    fs >> n;
		    fs >> k;
		    if (k != 0) {
			    cerr << "tsp sol: invalid origin" << endl;
			    exit(1);
		    }

		    auto org = vg;
    		vg.resize(n);
		    for (int i = 0; i < n; i++) {
			    fs >> k;
			    vg[i] = org[k - 1];
		    }

		    cerr << "loaded:" << sol_file << endl;
    	} else {
		    cerr << "sol file not found:" << sol_file << endl;
    	}
    }

	ChokudaiSearch cs(vg, false);
	cs.Run(envInt("MAXTURN", 1000), envInt("TIMEOUT", 60 * 1000));
	auto bests = cs.GetBests();
	vector<int> moves;
	for (const auto& best : bests) {
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
		auto& best = bests.back();
		cerr << "Not found ... next_index=" << best.next_index << " score=" << best.score << endl;
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
