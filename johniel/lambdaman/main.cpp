// github.com/Johniel/contests
// johniel/lambdaman/main.cpp

#include <bits/stdc++.h>

#define each(i, c) for (auto& i : c)
#define unless(cond) if (!(cond))

using namespace std;

template<typename P, typename Q> ostream& operator << (ostream& os, pair<P, Q> p);
template<typename P, typename Q> istream& operator >> (istream& is, pair<P, Q>& p);
template<typename P, typename Q, typename R> ostream& operator << (ostream& os, tuple<P, Q, R> t) { os << "(" << get<0>(t) << "," << get<1>(t) << "," << get<2>(t) << ")"; return os; }
template<typename P, typename Q, typename R> istream& operator >> (istream& is, tuple<P, Q, R>& t) { is >> get<0>(t) >> get<1>(t) >> get<2>(t); return is; }
template<typename T> ostream& operator << (ostream& os, vector<T> v) { os << "("; for (auto& i: v) os << i << ","; os << ")"; return os; }
template<typename T> istream& operator >> (istream& is, vector<T>& v) { for (auto& i: v) is >> i; return is; }
template<typename T> ostream& operator << (ostream& os, set<T> s) { os << "set{"; for (auto& i: s) os << i << ","; os << "}"; return os; }
template<typename K, typename V> ostream& operator << (ostream& os, map<K, V> m) { os << "map{"; for (auto& i: m) os << i << ","; os << "}"; return os; }
template<typename E, size_t N> istream& operator >> (istream& is, array<E, N>& a) { for (auto& i: a) is >> i; return is; }
template<typename E, size_t N> ostream& operator << (ostream& os, array<E, N>& a) { os << "[" << N << "]{"; for (auto& i: a) os << i << ","; os << "}"; return os; }
template<typename T> ostream& operator << (ostream& os, stack<T> s) { os << "stack{"; while (s.size()) { os << s.top() << ","; s.pop(); } os << "}"; return os; }
template<typename T> ostream& operator << (ostream& os, queue<T> q) { os << "queue{"; while (q.size()) { os << q.front() << ","; q.pop(); } os << "}"; return os; }
template<typename T> ostream& operator << (ostream& os, deque<T> q) { os << "deque{"; for (int i = 0; i < q.size(); ++i) os << q[i] << ","; os << "}"; return os; }
template<typename T> ostream& operator << (ostream& os, priority_queue<T> q) { os << "heap{"; while (q.size()) { os << q.top() << ","; q.pop(); } os << "}"; return os; }
template<typename P, typename Q> ostream& operator << (ostream& os, pair<P, Q> p) { os << "(" << p.first << "," << p.second << ")"; return os; }
template<typename P, typename Q> istream& operator >> (istream& is, pair<P, Q>& p) { is >> p.first >> p.second; return is; }

template<typename T> inline T setmax(T& a, T b) { return a = std::max(a, b); }
template<typename T> inline T setmin(T& a, T b) { return a = std::min(a, b); }

__attribute__((constructor)) static void _____(void) { ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.setf(ios_base::fixed); cout.precision(15); return ; }

using lli = long long int;
using ull = unsigned long long;
using str = string;
template<typename T> using vec = vector<T>;

uint32_t xorshift(void)
{
  // https://shindannin.hatenadiary.com/entry/2021/03/06/115415
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

const str g[] = {
  "############################",
  "#............##............#",
  "#.####.#####.##.#####.####.#",
  "#.####.#####.##.#####.####.#",
  "#.####.#####.##.#####.####.#",
  "#..........................#",
  "#.####.##.########.##.####.#",
  "#.####.##.########.##.####.#",
  "#......##....##....##......#",
  "######.##############.######",
  "######.##############.######",
  "######.##..........##.######",
  "######.##.###..###.##.######",
  "######.##.#......#.##.######",
  "#.........#......#.........#",
  "######.##.#......#.##.######",
  "######.##.########.##.######",
  "######.##..........##.######",
  "######.##.########.##.######",
  "######.##.########.##.######",
  "#............##............#",
  "#.####.#####.##.#####.####.#",
  "#.####.#####.##.#####.####.#",
  "#...##................##...#",
  "###.##.##.########.##.##.###",
  "###.##.##.########.##.##.###",
  "#......##....##....##......#",
  "#.##########.##.##########.#",
  "#.##########.##.##########.#",
  "#..........................#",
  "############################"};

const int h = 31;
const int w = 28;
const pair<int, int> src = make_pair(23, 12);
constexpr int DIR = 4;
constexpr array<int, DIR> di({0, 1, -1, 0});
constexpr array<int, DIR> dj({1, 0, 0, -1});
const str dirstr = "RDUL";

int name[h][w];
bool taboo[h][w][h][w];

bool is_inside(int i, int j) {
  return (0 <= i && i < h) && (0 <= j && j < w);
}

bool is_connected(void) {
  static bool vis[h][w];
  fill(&vis[0][0], &vis[h - 1][w - 1] + 1, false);
  function<int(int, int)> rec = [&] (int i, int j) {
    vis[i][j] = true;
    for (int d = 0; d < DIR; ++d) {
      int ni = i + di[d];
      int nj = j + dj[d];
      if (is_inside(ni, nj) && !vis[ni][nj] && !taboo[i][j][ni][nj]) rec(ni, nj);
    }
  }(src.first, src.second);
  int dot = 0;
  int visited = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      dot += (g[i][j] == '.');
      visited += vis[i][j];
    }
  }
  return dot == visited;
}

str solve(const vec<pair<pair<int, int>, pair<int, int>>>& blocked)
{
  {
    const int connected = xorshift() % blocked.size();
    auto [a, b] = blocked[connected];
    auto [ai, aj] = a;
    auto [bi, bj] = b;
    taboo[ai][aj][bi][bj] = true;
    taboo[bi][bj][ai][aj] = true;
  }
  static bool scc[h][w];
  {
    fill(&scc[0][0], &scc[h - 1][w - 1] + 1, false);
    static bool vis[h][w];
    fill(&vis[0][0], &vis[h - 1][w - 1] + 1, false);
    try {
      function<bool(int, int, int, int)> rec = [&] (int i, int j, int pi, int pj) {
        vis[i][j] = true;
        for (int d = 0; d < DIR; ++d) {
          int ni = i + di[d];
          int nj = j + dj[d];
          if (pi == ni && pj == nj) continue;
          if (is_inside(ni, nj)) {
            if (vis[ni][nj]) return scc[i][j] = scc[ni][nj] = true;            
            if (rec(ni, nj)) {
              // if (scc[i][j]) throw "";
              return scc[i][j] = scc[ni][nj] = true;
            }
          }
        }
        return false;
      }(src.first, src.second, src.first, src.second);
    } catch (const char* e) {
    }
  }

  pair<int, int> curr = src;
  while (true) {
    auto [i, j] = curr;
    pair<int, int> next = make_pair(-1, -1);
    char d = 0;
    for (int d = 0; d < DIR; ++d) {
      int ni = i + di[d];
      int nj = j + dj[d];
      if (is_inside(ni, nj) && !vis[ni][nj]){
        if (scc[ni][nj]) {
          next = make_pair(ni, nj);
          d = dirstr[d];
        } else {
        }
      }
    }
  }
  
  return ;
}

#include <random>
template<typename T>
void vshuffle(vec<T>& v)
{
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(v.begin(), v.end(), engine);
  return ;
};

int main(int argc, char *argv[])
{
  {
    int cnt = 0;
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        name[i][j] = cnt++;
      }
    }
  }
  fill(&taboo[0][0][0][0], &taboo[h - 1][w - 1][h - 1][w - 1] + 1, false);

  vec<pair<pair<int, int>, pair<int, int>>> candidates;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      unless (g[i][j] == '.') continue;
      for (int d = 0; d < DIR; ++d) {
        int ni = i + di[d];
        int nj = j + dj[d];
        if (is_inside(ni, nj) && g[ni][nj] == '.') {
          pair<int, int> a = make_pair(i, j);
          pair<int, int> b = make_pair(ni, nj);
          unless (a < b) swap(a, b);
          candidates.push_back(make_pair(a, b));
        }
      }      
    }
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

    vshuffle(candidates);

    vec<pair<pair<int, int>, pair<int, int>>> blocked;
    for (int i = 0; i < candidates.size(); ++i) {
      auto [a, b] = candidates[i];
      auto [ai, aj] = a;
      auto [bi, bj] = b;
      taboo[ai][aj][bi][bj] = true;
      taboo[bi][bj][ai][aj] = true;
      unless (is_connected()) {
        blocked.push_back(candidates[i]);
        taboo[ai][aj][bi][bj] = false;
        taboo[bi][bj][ai][aj] = false;
      }
    }

    solve(blocked);
  }
  
  return 0;
}
