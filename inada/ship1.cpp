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

int envInt(const char *name, int defaultValue) {
    auto s = getenv(name);
    if (s != nullptr) return atoi(s);
    return defaultValue;
}

std::string envStr(const char *name, const char *defaultValue) {
    auto s = getenv(name);
    if (s != nullptr) return s;
    return "";
}

using StageData = vector<tuple<int, int> >;

class MoveDatabase {
    // やりたいこと
    // クエリ1: p0, v0 から p1 に移動するときの v1の候補を返却する
    //   探索時に使用する.
    // クエリ2: p0, v0 から p1, v1 に移動する a の配列を返却する
    //   経路復元時に使用する.

public:
    static const int T = 100;
    static const int X = T * T;

    // テーブル生成
    // dp[t][x] = set(v)
    // tターン後にxに到達する時のv (存在しない場合は空)
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
    vector<tuple<int, int, int> > FindCandidates(int x0, int y0, int vx0, int vy0, int x1, int y1) const {
        vector<tuple<int, int, int> > candidates; // t, vx, vy
        set<tuple<int, int> > used;

        const int max_xy = max(abs(x1 - x0), abs(y1 - y0));
        // const int t0 = max_xy * (max_xy + 1) / 2;
        int max_t = T;
        for (int t = 0; t < max_t; t++) {
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
        vector<char> ops(t);
        for (int i = 0; i < t; i++) {
            ops[i] = '5' + 3 * ya[i] + xa[i];
        }
        return {ops.begin(), ops.end()};
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
        auto test_cases = vector<tuple<int, int, int, int, int> >{
            {1, 0, 0, 1, 1},
            {10, 0, 0, 10, 0},
            {10, 0, 0, -10, 0},
            {10, 0, 0, 10, 2},
            {10, 0, 0, 0, -2},
        };

        for (const auto &[t, x0, v0, x1, v1]: test_cases) {
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
        auto test_cases = vector<tuple<int, int, int, int, int> >{
            {1, 0, 0, 1, 1},
            {10, 0, 0, 55, 10},
            {10, 10, 0, 65, 10},
            {1, -1, 1, 0, 1},
            {1, 1, -1, 0, -1},
            {1, 1, -1, 1, 0},
        };

        for (const auto &[t, x0, v0, x1, v1]: test_cases) {
            auto vs = GetVel1d(t, x0, v0, x1);
            mm_assert(!vs.empty());
            cerr << "vs=";
            for (auto &v: vs) {
                cerr << v << " ";
            }
            cerr << endl;
            cerr << "v1=" << v1 << endl;
            mm_assert(find(vs.begin(), vs.end(), v1) != vs.end());
        }
    }

private:
    // dp[t][x] = v;
    vector<vector<set<int> > > dp;
};

StageData input(istream &is) {
    StageData vg;
    int x, y;
    string s;
    while (getline(is, s)) {
        if (s[0] == '#') continue;
        stringstream ss(s);
        ss >> x >> y;
        vg.push_back(make_pair(x, y));
    }
    return vg;
}

template<typename T>
class Ranking {
public:
    void push(const T &value) {
        m_.insert(value);
        if (size() == n + 1) {
            pop_min();
        }
    }

    T min_element() {
        assert(!empty());
        return *m_.begin();
    }

    const T &min_element() const {
        assert(!empty());
        return *m_.begin();
    }

    T max_element() {
        assert(!empty());
        return *m_.rbegin();
    }

    const T &max_element() const {
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

    bool empty() const { return m_.empty(); }

    size_t size() const { return m_.size(); }

    void clear() { m_.clear(); }

    const std::multiset<T> &data() const { return m_; }

private:
    int n = envInt("WIDTH", 1000);
    std::multiset<T> m_;
};

class ChokudaiSearch {
public:
    struct SearchNode {
        int t{}, vx{}, vy{};
        std::shared_ptr<SearchNode> parent;
        bool operator<(const SearchNode &o) const { return t > o.t; }
    };

    ChokudaiSearch(const ChokudaiSearch &) = delete;

    ChokudaiSearch(ChokudaiSearch &&) = delete;

    ChokudaiSearch &operator=(const ChokudaiSearch &) = delete;

    ChokudaiSearch() = delete;

    explicit ChokudaiSearch(const MoveDatabase& db, StageData stage_data)
        : db_(db), stage_data_(std::move(stage_data)) {
        ranking_.resize(stage_data_.size() + 1);
        bests_.resize(stage_data_.size());
        mutex_.resize(stage_data_.size() + 1);

        for (auto &m: mutex_) {
            m = std::make_unique<std::mutex>();
        }

        for (auto &best: bests_) {
            best.t = INT_MAX;
        }

        SearchNode node{0, 0, 0, nullptr};
        ranking_[0].push(node);
    }

    std::vector<SearchNode> GetBests() const {
        return bests_;
    }

    void Run(int target_depth, int timeout_ms = 2000) {
        auto f = [this, target_depth, timeout_ms]() {
            const auto t0 = high_resolution_clock::now();
            while (true) {
                const auto updated = RunInternal(20);
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
    bool RunInternal(int loop_count) {
        SearchNode node, tmp_node;
        bool updated = true;

        for (int loop = 0; updated && loop < loop_count; ++loop) {
            updated = false;

            for (int index = 0; index < stage_data_.size(); ++index) {
                {
                    std::lock_guard lock(*mutex_[index]);
                    auto &prev = ranking_[index];
                    if (prev.empty()) {
                        continue;
                    }

                    node = prev.max_element();
                    prev.pop_max();
                    updated = true;
                }

                auto [x0, y0] = index == 0 ? make_tuple(0, 0) : stage_data_[index-1];
                auto [x1, y1] = stage_data_[index];
                auto candidates = db_.FindCandidates(x0, y0, node.vx, node.vy, x1, y1);
                for (const auto &[dt, vx1, vy1]: candidates) {
                    tmp_node.t = node.t + dt;
                    tmp_node.vx = vx1;
                    tmp_node.vy = vy1;
                    tmp_node.parent = std::make_shared<SearchNode>(node);

                    {
                        std::lock_guard lock(*mutex_[index]);
                        auto &best = bests_[index];
                        if (tmp_node.t < best.t) {
                            best = tmp_node;
                        }
                    }

                    /*
                    {
                        const auto h = Hash(node.t + dt, vx1, vy1);
                        const auto h2 = static_cast<uint16_t>(h ^ h >> 16 ^ h >> 32 ^ h >> 48);

                        std::lock_guard g_lock(g_mutex_);
                        auto &hash_pool = weak_hash_;
                        if (hash_pool[h2] == h) {
                            continue;
                        }
                        hash_pool[h2] = h;
                    }
                    */

                    {
                        std::lock_guard lock(*mutex_[index + 1]);
                        ranking_[index + 1].push(tmp_node);
                    }
                }
            }

        }

        return updated;
    }


    static uint64_t Hash(int t, int vx, int vy) {
        uint64_t ret = 37;
        ret = ret * 573292817ULL + t;
        ret = ret * 573292817ULL + vx;
        ret = ret * 573292817ULL + vy;
        return ret;
    }

    const MoveDatabase& db_;
    StageData stage_data_;
    std::array<uint64_t, 1 << 16> weak_hash_{};
    std::vector<SearchNode> bests_;
    std::vector<Ranking<SearchNode> > ranking_;
    std::vector<std::unique_ptr<std::mutex> > mutex_;
    std::mutex g_mutex_{};
};

string solve_greedy(const MoveDatabase &db, const StageData &vg) {
    int t = 0;
    int x = 0;
    int y = 0;
    int vx = 0;
    int vy = 0;
    string cmds;
    for (int i = 0; i < vg.size(); i++) {
        auto [x1, y1] = vg[i];
        auto debug = vector{x, y, vx, vy, x1, y1};
        DUMPV(debug);
        auto candidates = db.FindCandidates(x, y, vx, vy, x1, y1);
        mm_assert(!candidates.empty());
        auto [dt, vx1, vy1] = candidates[0];
        cerr << i + 1 << "/" << vg.size() << " candidate dt, vx1, vy1 = " << dt << " " << vx1 << " " << vy1 << endl;
        cmds += db.GetCommands(dt, x, y, vx, vy, x1, y1, vx1, vy1);
        cerr << "GetCommands ok" << endl;
        t += dt;
        x = x1;
        y = y1;
        vx = vx1;
        vy = vy1;
    }
    return cmds;
}

string solve_chokudai_search(const MoveDatabase &db, const StageData &vg) {
    ChokudaiSearch cs(db, vg);
    cs.Run(envInt("TIMEOUT", 1000));
    auto node = cs.GetBests().back();
    auto [x1, y1] = vg.back();
    deque<string> cmds_vec;
    for (int i = static_cast<int>(vg.size()) - 2; 0 <= i; i--) {
        auto [x0, y0] = vg[i];
        auto cmds = db.GetCommands(node.t - node.parent->t, x0, y0, node.parent->vx, node.parent->vy, x1, y1, node.vx, node.vy);
        cmds_vec.push_front(cmds);
        x1 = x0;
        y1 = y0;
        node = *node.parent;
    }
    auto cmds = db.GetCommands(node.t, 0, 0, 0, 0, x1, y1, node.vx, node.vy);
    cmds_vec.push_front(cmds);

    string ret;
    for (const auto &cmd : cmds_vec) {
        ret += cmd;
    }
    return ret;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "need problem file path" << endl;
        exit(1);
    }

    MoveDatabase db;
    db.BuildTable();
    db.TestGetAcc1d();
    db.TestGetVel1d();

    ifstream ifs(argv[1]);
    auto vg = input(ifs);
    ifs.close();
    cerr << "vg.size()=" << vg.size() << endl;

    cout << solve_greedy(db, vg) << endl;
    cout << solve_chokudai_search(db, vg) << endl;
}
