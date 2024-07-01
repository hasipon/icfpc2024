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

// constexpr lli mod = 1e9 + 7;
constexpr lli mod = 998244353;
// constexpr lli mod = 65087;
// constexpr lli mod = 9808358;
//                  10619620 (/ 998244353 94)
//                  2098960
//                  9152052


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

void l10_old()
{
  const int X = 16;

  for (int k = 0; k < 4; ++k) {
    cout << "UUUU" << endl;
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 16; ++j) {
        cout << str(X, 'R');
        cout << "DRRU";
      }
      cout << "LDR";
      for (int j = 0; j < 16; ++j) {
        cout << str(X, 'L');
        cout << "DLLU";
      }
      cout << "RDL";
    }
  }
  cout << "RRURRDRRRRRRRRRURRDRRRRRRRRRURRDRRRRRRRRRURRDRRRRRRRRR" << endl;

  return ;
}

void l16(void)
{
  for (int _ = 0; _ < 100; ++_) {
    cout << str(17, 'R');
    cout << str(21, 'D');
    cout << str(7, 'L');
    cout << str(11, 'U');
  }
  cout << endl;

  return ;
}

vec<lli> l4(void)
{
  constexpr lli mod = 998244353;
  const int h = 21;
  const int w = 21;
  str g[h] = {
    str("#####################"),
    str("#...#.#.........#...#"),
    str("#.###.#.#####.###.###"),
    str("#...#.#.....#.......#"),
    str("###.#.#.###.#########"),
    str("#.#....L..#.#.......#"),
    str("#.#####.###.#.###.###"),
    str("#.#.#...#.......#...#"),
    str("#.#.#######.#######.#"),
    str("#.#...#.#...#.#.....#"),
    str("#.#.###.#.###.###.#.#"),
    str("#.....#...#.......#.#"),
    str("#.###.###.###.#####.#"),
    str("#.#.#...#...#...#...#"),
    str("###.#.#.#.#####.###.#"),
    str("#...#.#...#.....#...#"),
    str("#.###.#.#.#####.#####"),
    str("#.....#.#.....#.#...#"),
    str("#.###.#.#.#.#.#.#.###"),
    str("#.#...#.#.#.#.#.....#"),
    str("#####################")
  };

  pair<int, int> src = make_pair(1 << 29, 1 << 29);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (g[i][j] == 'L') {
        src = make_pair(i, j);
        g[i][j] = '.';
        i = j = (1 << 28);
      }
    }
  }

  int dot = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      dot += (g[i][j] == '.');
    }
  }

  int mx = 0;
  int vis[h][w];
  fill(&vis[0][0], &vis[h - 1][w - 1] + 1, -1);
  for (lli loop = 0; ; ++loop) {
    lli x = xorshift() % 94;
    lli mult = xorshift() % mod;
    if (94 <= mult) continue;
    const pair<lli, lli> seed = make_pair(x, mult);
    pair<int, int> curr = src;
    vis[src.first][src.second] = loop;
    int visited = 1;
    vec<lli> v;
    constexpr array<int, 8> di({0, 1, -1, 0, 1, -1, 1, -1});
    constexpr array<int, 8> dj({1, 0, 0, -1, 1, -1, -1, 1});
    for (int _ = 0; _ < 50000; ++_) {
      v.push_back(x);
      (x *= mult) %= mod;
    }
    // reverse(v.begin(), v.end());

    lli mn = 1LL << 60;
    each (x, v) {
      auto [i, j] = curr;
      int d = x % 4;
      int ni = i + di[d];
      int nj = j + dj[d];
      if (g[ni][nj] == '.') {
        curr = make_pair(ni, nj);
        visited += (vis[ni][nj] != loop);
        vis[ni][nj] = loop;
        if (visited == dot) setmin(mn, x);
      }
    }

    // if (94 <= mn) continue;
    if (94*94 <= mn) continue;
    if (dot == visited) {
      for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
          if (vis[i][j] == loop) cout << "@";
          else cout << g[i][j];
        }
        cout << endl;
      }
      // cout << v << endl;
      cout << v.size() << endl;
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
      assert(0 < v.front());
      cout << v.size() << endl;
      cout << "ini, mult, mod, fin" << endl;
      cout << make_pair(seed, mod) << ' ' << mn << endl;
      return vec<lli>({seed.first, seed.second, mod, mn});
    }
  }

  return {};
}

vec<lli> l7(void)
{
  const int h = 31;
  const int w = 28;
  str g[h] = {
    str("############################"),
    str("#............##............#"),
    str("#.####.#####.##.#####.####.#"),
    str("#.####.#####.##.#####.####.#"),
    str("#.####.#####.##.#####.####.#"),
    str("#..........................#"),
    str("#.####.##.########.##.####.#"),
    str("#.####.##.########.##.####.#"),
    str("#......##....##....##......#"),
    str("######.##############.######"),
    str("######.##############.######"),
    str("######.##..........##.######"),
    str("######.##.###..###.##.######"),
    str("######.##.#......#.##.######"),
    str("#.........#......#.........#"),
    str("######.##.#......#.##.######"),
    str("######.##.########.##.######"),
    str("######.##..........##.######"),
    str("######.##.########.##.######"),
    str("######.##.########.##.######"),
    str("#............##............#"),
    str("#.####.#####.##.#####.####.#"),
    str("#.####.#####.##.#####.####.#"),
    str("#...##........L.......##...#"),
    str("###.##.##.########.##.##.###"),
    str("###.##.##.########.##.##.###"),
    str("#......##....##....##......#"),
    str("#.##########.##.##########.#"),
    str("#.##########.##.##########.#"),
    str("#..........................#"),
    str("############################")
  };

  pair<int, int> src = make_pair(1 << 29, 1 << 29);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (g[i][j] == 'L') {
        src = make_pair(i, j);
        g[i][j] = '.';
        i = j = (1 << 28);
      }
    }
  }

  int dot = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      dot += (g[i][j] == '.');
    }
  }

  int mx = 0;
  int vis[h][w];
  fill(&vis[0][0], &vis[h - 1][w - 1] + 1, -1);
  for (lli loop = 0; ; ++loop) {
    // lli x = xorshift() % mod;
    lli x = 1;
    lli mult = xorshift() % mod;
    const pair<lli, lli> seed = make_pair(x, mult);
    pair<int, int> curr = src;
    vis[src.first][src.second] = loop;
    int visited = 1;
    vec<lli> v;
    constexpr array<int, 8> di({0, 1, -1, 0, 1, -1, 1, -1});
    constexpr array<int, 8> dj({1, 0, 0, -1, 1, -1, -1, 1});
    for (int _ = 0; _ < 12000; ++_) {
      auto [i, j] = curr;
      v.push_back(x);
      int d = x % 4;
      (x *= mult) %= mod;
      {
        int ni = i + di[d];
        int nj = j + dj[d];
        if (g[ni][nj] == '.') {
          curr = make_pair(ni, nj);
          visited += (vis[ni][nj] != loop);
          vis[ni][nj] = loop;
        }
      }
    }

    if (dot == visited) {
      for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
          if (vis[i][j] == loop) cout << "@";
          else cout << g[i][j];
        }
        cout << endl;
      }
      // cout << v << endl;
      cout << v.size() << endl;
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
      assert(0 < v.front());
      cout << v.size() << endl;
      cout << "ini, mult, mod, fin" << endl;
      cout << make_pair(seed, mod) << ' ' << x << endl;
      return vec<lli>({seed.first, seed.second, mod, x});
    }
  }

  return {};
}

vec<lli> l10(void)
{
  const int h = 50;
  const int w = 50;
  str g[h] = {
    str("L..........#..........#..........#..........#....."),
    str(".....#..........#..........#..........#..........#"),
    str("..........#..........#..........#..........#......"),
    str("....#..........#..........#..........#..........#."),
    str(".........#..........#..........#..........#......."),
    str("...#..........#..........#..........#..........#.."),
    str("........#..........#..........#..........#........"),
    str("..#..........#..........#..........#..........#..."),
    str(".......#..........#..........#..........#........."),
    str(".#..........#..........#..........#..........#...."),
    str("......#..........#..........#..........#.........."),
    str("#..........#..........#..........#..........#....."),
    str(".....#..........#..........#..........#..........#"),
    str("..........#..........#..........#..........#......"),
    str("....#..........#..........#..........#..........#."),
    str(".........#..........#..........#..........#......."),
    str("...#..........#..........#..........#..........#.."),
    str("........#..........#..........#..........#........"),
    str("..#..........#..........#..........#..........#..."),
    str(".......#..........#..........#..........#........."),
    str(".#..........#..........#..........#..........#...."),
    str("......#..........#..........#..........#.........."),
    str("#..........#..........#..........#..........#....."),
    str(".....#..........#..........#..........#..........#"),
    str("..........#..........#..........#..........#......"),
    str("....#..........#..........#..........#..........#."),
    str(".........#..........#..........#..........#......."),
    str("...#..........#..........#..........#..........#.."),
    str("........#..........#..........#..........#........"),
    str("..#..........#..........#..........#..........#..."),
    str(".......#..........#..........#..........#........."),
    str(".#..........#..........#..........#..........#...."),
    str("......#..........#..........#..........#.........."),
    str("#..........#..........#..........#..........#....."),
    str(".....#..........#..........#..........#..........#"),
    str("..........#..........#..........#..........#......"),
    str("....#..........#..........#..........#..........#."),
    str(".........#..........#..........#..........#......."),
    str("...#..........#..........#..........#..........#.."),
    str("........#..........#..........#..........#........"),
    str("..#..........#..........#..........#..........#..."),
    str(".......#..........#..........#..........#........."),
    str(".#..........#..........#..........#..........#...."),
    str("......#..........#..........#..........#.........."),
    str("#..........#..........#..........#..........#....."),
    str(".....#..........#..........#..........#..........#"),
    str("..........#..........#..........#..........#......"),
    str("....#..........#..........#..........#..........#."),
    str(".........#..........#..........#..........#......."),
    str("...#..........#..........#..........#..........#..")
  };
  assert(g[0].size() == w);

  pair<int, int> src = make_pair(1 << 29, 1 << 29);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (g[i][j] == 'L') {
        src = make_pair(i, j);
        g[i][j] = '.';
        i = j = (1 << 28);
      }
    }
  }

  int dot = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      dot += (g[i][j] == '.');
    }
  }

  constexpr lli mod = 998244353;

  int mx = 0;
  int vis[h][w];
  fill(&vis[0][0], &vis[h - 1][w - 1] + 1, -1);
  for (lli loop = 0; ; ++loop) {
    lli x = xorshift() % mod;
    lli mult = xorshift() % mod;

    if (94*94 <= mult) continue;
    const pair<lli, lli> seed = make_pair(x, mult);
    pair<int, int> curr = src;
    vis[src.first][src.second] = loop;
    int visited = 1;
    vec<lli> v;
    constexpr array<int, 8> di({0, 1, -1, 0, 1, -1, 1, -1});
    constexpr array<int, 8> dj({1, 0, 0, -1, 1, -1, -1, 1});
    for (int _ = 0; _ < 40000; ++_) {
      v.push_back(x);
      (x *= mult) %= mod;
    }
    reverse(v.begin(), v.end());

    lli mn = 1LL << 60;
    each (x, v) {
      auto [i, j] = curr;
      int d = x % 4;
      int ni = i + di[d];
      int nj = j + dj[d];
      unless (0 <= ni && ni < h) continue;
      unless (0 <= nj && nj < w) continue;
      if (g[ni][nj] == '.') {
        curr = make_pair(ni, nj);
        visited += (vis[ni][nj] != loop);
        vis[ni][nj] = loop;
        if (visited == dot) setmin(mn, x);
      }
    }
    mn = v.front();

    if (dot == visited) {
      for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
          if (vis[i][j] == loop && vis[i][j] != -1) cout << "@";
          else cout << g[i][j];
        }
        cout << endl;
      }
      // cout << v << endl;
      cout << v.size() << endl;
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
      assert(0 < v.front());
      cout << v.size() << endl;
      cout << "ini, mult, mod, fin" << endl;
      cout << make_pair(seed, mod) << ' ' << mn << endl;
      return vec<lli>({seed.first, seed.second, mod, mn});
    }
  }

  return {};
}

vec<lli> l11(void)
{
  const int h = 101;
  const int w = 101;
  str g[h] = {
    str("#####################################################################################################"),
    str("#.#.....#.......#.#.......#...#...#.......#...#.......#.#.......#...#.....#.....#.....#.......#.....#"),
    str("#.###.###.#####.#.###.###.#.###.#.#.#######.#######.###.#.###.###.#####.#.###.#######.#.#.#########.#"),
    str("#...#.#.....#.....#.....#...#...#.....#.........#.#.......#...#.........#.....#...#.#...#.#.........#"),
    str("#.###.###.###.#.#########.#.#.###.#.#.#.###.#.###.###.#################.#######.#.#.###.###.#.###.###"),
    str("#.#.#.....#...#...#.#.#...#.#.#...#.#.#...#.#.#...........#.....#.......#.#.#...#.#.........#...#...#"),
    str("#.#.###.###.#######.#.#.#######.#####.#.#.###.###.#.#####.#####.#.###.#.#.#.###.#.#.#####.#####.#####"),
    str("#.......#.#.#.....#.........#.....#...#.#...#...#.#.#...#.#...#.#...#.#.#.....#.#.....#.....#.#.....#"),
    str("#####.#.#.###.#.###.#.###.#.#.#######.#.#.###.###.#.#.#######.#.###.#####.###.###.#.#.#.###.#.#.###.#"),
    str("#...#.#.#...#.#...#.#...#.#.......#.#.#.#.#.#...#.#.#.......#.......#.....#...#.#.#.#.#.#.....#.#.#.#"),
    str("###.###.#.###.#####.#######.#.#####.#.#.###.#######.#####.#.#####.#.#.#.#####.#.#.###########.#.#.###"),
    str("#...#.........#.........#.#.#.#...#.........#.........#.#.#...#...#...#...#...#.#...#...#.....#.....#"),
    str("###.#.#.#.###.#####.#.###.###.###.###.#############.###.#####.###.###.###.#.###.###.#.###.#########.#"),
    str("#.#...#.#.#...#.....#.#.....#.#.#...#.....#...#...#.#.............#...#...#.#.....#.#...#.........#.#"),
    str("#.###.###.###.###.#####.###.#.#.###.###.###.#####.#.#.###.#############.###.#####.#.#.###.#####.#####"),
    str("#.....#.....#.........#.#.....#...#.........#.#.#...#...#.......#...#.#.#...#...#.....#.....#.......#"),
    str("#.#.###.###.#.#.#################.#.#####.###.#.#.#.#.#####.###.###.#.#######.###.#####.#.###.###.###"),
    str("#.#.#.#.#...#.#...#...#...#...#.......#...#.#...#.#.#.....#.#...#.....#...........#.....#.#.#...#.#.#"),
    str("#.###.###.#.#######.###.#####.#.###.#.#.###.#.###.#############.###.###.###.###.###########.#.#.###.#"),
    str("#.#.....#.#.#.....#.#.......#.#...#.#.#.#...#.......#.#.....#.#.#.....#.#.....#.#.......#...#.#.#.#.#"),
    str("#.###.#######.#####.#.###.###.#.###.#.#####.#.#.#####.###.###.#.#.#######.#####.#.###.###.###.#.#.#.#"),
    str("#.#...#...#.....#.#...#...#.#.#.#...#.#.#.....#.#...#.....#...#.#.....#...#.......#.........#.#.....#"),
    str("###.#.###.#.#.###.#.#.#.#.#.#.###.#####.###.#.#####.###.#.#.###.#####.###.#.###.#######.###########.#"),
    str("#...#.#.#...#...#...#.#.#...#.#.#.#.........#.#...#...#.#.............#...#.#.......#.....#.....#.#.#"),
    str("###.###.#.###.#####.#######.#.#.#.#######.###.#.#####.#.#.#####.###.#.#.###########.#########.#.#.###"),
    str("#...#.#...#.#.#.#...#.....#.....#.......#...#.#...#.....#.#...#...#.#.#.#...#.#.#.....#.....#.#.....#"),
    str("#.###.#.###.#.#.#.#####.###.#####.#.#.#####.###.#####.#####.#######.#######.#.#.#####.#.#.###.#.#.#.#"),
    str("#.....#.#.#...#.#.....#...#...#.#.#.#.......#...............#.....#...#.....#.........#.#...#.#.#.#.#"),
    str("#.###.###.###.#.#.#.###.#####.#.#.#######.#.###########.###.#.#########.#.#########.#.#.###########.#"),
    str("#.#.#...#.#.......#.#...#...#L#.......#.#.#.....#...#...#.#.#.#...#.#...#...#.#.....#.....#.....#.#.#"),
    str("#.#.###.#.#####.###.###.###.###.###.###.###########.#.###.###.###.#.#.#######.###.###.#.#####.###.#.#"),
    str("#.#...........#.#.....#.#.#...#...#.#...#.......#.#.#...........#.....#.#.......#.#...#.#.....#.#...#"),
    str("###.###.###.###.###.###.#.#.###.#####.#.#.#.#####.#.#.#########.#.###.#.#.#.#.#####.#########.#.#.###"),
    str("#...#...#.#...#.#...#.#.#.....#.....#.#.#.#.............#.#.....#.#.#.....#.#.#.........#.#.....#...#"),
    str("#######.#.#########.#.#.###.#####.###.###.#######.#####.#.#####.###.#.###.###.#.###.#.###.###.#.#.###"),
    str("#.....#.........#...#.......#...#.#.......#.#...#.#...........#.#.....#.....#.#.#.#.#.....#...#.....#"),
    str("###.###.###.#.###.#.#.#####.###.#.#####.###.###.#.###.#.#.#.#######.#####.###.###.#.###.#####.#.#####"),
    str("#.#...#.#...#.#...#.#.#...#...#.......#.....#.......#.#.#.#...#.......#.....#.#...#...#...#.#.#.....#"),
    str("#.#.#######.###.#########.#.###.#####.###.#.#.#######.#######.#.#.#.#######.#####.#.#.#.#.#.#######.#"),
    str("#.#.......#.....#.....#.....#...#.......#.#.#...#.....#.#...#...#.#.....#.#.#...#...#.#.#...#.#...#.#"),
    str("#.#.#.###.#####.#.#######.#####.#############.#########.###.#.#########.#.#####.#.###.#.#####.#.#.#.#"),
    str("#.#.#.#.#.#.....#.....#.....#.................#...#.....#.........#.........#...#.#...#.........#...#"),
    str("#.###.#.#.#.#.###.###.###############.###.#####.#.#####.#.#.###.#########.###.#####.###.###.#.#######"),
    str("#...#.#.....#...#.#...#.#.........#.....#...#.#.#...#...#.#.#...#...#...#.#.#.#.#.#.#.#.#...#...#...#"),
    str("#.###.###.###.###.###.#.#.###.#.###.#######.#.#.#.#.###.#.#######.#.#.#.###.#.#.#.###.#.#####.#.#.###"),
    str("#.......#.#...#.#...#...#.#.#.#.........#.....#.#.#...#...#...#.#.#...#.#.......#.#.#.......#.#.#...#"),
    str("#.###.###.###.#.#.#####.###.#.###.#.#.###.###########.#.#####.#.#.###.###.#####.#.#.#.#####.###.#.#.#"),
    str("#...#.#.#.#...#...#.....#.#...#...#.#...#.#.........#...#...........#.....#.#...#.........#...#...#.#"),
    str("#.#.###.###.#######.#####.#.###############.#.#.###.#.###.#########.#######.#.#########.###.#####.###"),
    str("#.#.#.........#.#.....#.#.#.#.#...#...#.#.#.#.#...#...........#.#...#.#...........#...#...#...#.....#"),
    str("#####.#########.#.###.#.#.#.#.#.#.###.#.#.#.###############.###.#.###.#####.#.#.#####.#.#######.#.###"),
    str("#.........#.......#...#.......#.#.#...#.......#.....#.....#.#...#.....#.#...#.#.#...........#...#.#.#"),
    str("###.###.#######.###.#####.#####.#.#.#.###.#.###.###.#.#####.#.#####.#.#.#.#.#####.#####.#.#.#####.#.#"),
    str("#.....#.#.#.......#...#.#.....#.#...#...#.#...#.#.#.#.....#.#...#...#...#.#.......#.....#.#...#.....#"),
    str("###.#.###.#.###.#.#####.#.#########.###########.#.###.#########.#######.#########.#####.###########.#"),
    str("#...#.......#...#.....#.#.#.#.#.#.......#...#...#...#.....#...#.#.#...#.......#...#...#.#.......#...#"),
    str("#.#.#########.#.#.#.###.#.#.#.#.#.#.#####.#####.###.###.#####.#.#.###.#.###.###.#.#.#.###.###.###.#.#"),
    str("#.#...#.#.#...#.#.#.........#.#.#.#.#...#...........#.....#.#.#...#...#...#.#.#.#...#...#.#.#.#...#.#"),
    str("#.#####.#.###.#.#######.#.#.#.#.#.###.#######.###.###.#.#.#.#.#.#####.#######.#.###########.#.#####.#"),
    str("#.#.#.#.......#.#.......#.#.#.#...#.......#.....#...#.#.#.#.#...#.#.......#...#.#.....#.#.....#.....#"),
    str("###.#.#####.###########.###.#.#.#.#######.#.###.#.###.#.###.#.###.###.###.#.#.###.#####.#####.#.#.###"),
    str("#.....#.#.#...#.....#...#.#.....#.#.....#...#...#.#.#.#.....#.......#...#...#...#.#.......#.....#.#.#"),
    str("#.#####.#.#.#.#.###.###.#.#.#######.#####.#####.###.#.#######.#######.#.#####.###.#######.#####.###.#"),
    str("#.#...#.#...#...#...#.....#.....#.#.#.#.......#.....#...#.....#...#...#.#.#.#...#...#.#.....#.......#"),
    str("#.###.#.#.#.#.#####.#.#.###.#####.#.#.###.#.###.#######.#.#.#####.#####.#.#.#####.###.#.#.###.#.###.#"),
    str("#.......#.#.#.#.#...#.#.#.......#.#.......#.#.#.......#...#.#.#.#.#...#...............#.#.#...#...#.#"),
    str("#.#####.#.#####.#.#####.#.#.#####.###.#######.###.#.###.#.###.#.#.###.#####.#####.#######.###.#######"),
    str("#.#.#.#.........#...#.#.#.#...#.....#.#...#.....#.#...#.#.#...#.#...#...#...#.#...#.......#.......#.#"),
    str("###.#.#.#####.#######.###.###.#.#####.#.###.###.#.#.###.###.#.#.#.#.###.###.#.#######.###.#.#.###.#.#"),
    str("#.........#.....#.......#.#...#...........#...#...#...#...#.#.....#.#.........#.#.....#.#...#...#...#"),
    str("###.#####.#.#.#####.#####.#############.###.###.#####.#.#########.#########.###.#####.#.#.#######.#.#"),
    str("#...#.....#.#.#...#.#...#.....#...#.#.#...#.#.....#...#.........#...#.#.#...#.#.#.#.#.#...#.#.#.#.#.#"),
    str("###.###.###.#.###.#.#.###.#.#####.#.#.#########.###.###.###.###.###.#.#.###.#.#.#.#.#######.#.#.#.#.#"),
    str("#.#.#...#...#.#...#.....#.#.#.....#.....#.#...#.#.#.....#...#...#.......#.....#.#.....#.#.#.......#.#"),
    str("#.#####.#.#######.#.#.###.#.#.#.#.#####.#.#.#####.#.#########.#######.#####.###.#.#.#.#.#.#.#####.###"),
    str("#.....#.#.#...#...#.#.....#...#.#...#.#...#...#.#...#...........#.#.....#...#...#.#.#.#.#...#.#...#.#"),
    str("#.#.#####.#.###.###.#.#.#####.#######.#.###.###.#.#######.#####.#.#.#######.#.#####.#.#.#####.#.###.#"),
    str("#.#...#.#.#.#.#.#...#.#.#.............#.#.....#.....#.#...#.....#.#.....#.#...#.#.#.#...#.#...#.....#"),
    str("#.#.#.#.#.#.#.#.#####.###.#####.#######.#####.#.#####.#####.###.#.###.#.#.#.###.#.#####.#.###.#.###.#"),
    str("#.#.#.#...#...#.#.....#.#...#...#.#.#...#.....#...#.#.#.......#.....#.#...........#.......#.......#.#"),
    str("#.###.###.###.#.#.#####.#####.#.#.#.###.###.#####.#.#.#.###.#.#######.###.###.#.###.#####.#.###.###.#"),
    str("#...#.#.#.#.......#.......#.#.#.#...............#...#.#.#...#...#.#...#.....#.#.#.#.#.#...#...#.#...#"),
    str("#.#.###.#.#######.#.###.#.#.#.###.#########.#.#######.#######.###.#####.#########.###.###.#######.###"),
    str("#.#.#.#...#...#...#...#.#.#...#.#.#.#...#...#.#.....#.#...#.#.....#.#...#.#.......#.#.#.#.#.....#.#.#"),
    str("###.#.#######.#.#.#######.#####.#.#.###.#.###.#.#.#.#.#.###.#.#.###.###.#.#####.#.#.#.#.#.#.###.###.#"),
    str("#.......#.#.#...#...#.#.....#.....#.#.......#.#.#.#.....#.....#.......#.........#.#.........#.....#.#"),
    str("#####.###.#.#####.###.#.###.###.###.#####.#####.#####.#.###.###.###.#.#.#######.#.#.#.###.#######.#.#"),
    str("#.....#.#.....#...#...#...#...#.#.........#.....#.....#...#...#.#...#.....#...#.#...#...#.#.#.#.#...#"),
    str("#####.#.#.#.#.#.#####.#.#.#######.#.###.#.#.###.#.#.#.#.###.#####.#########.#.#####.#####.#.#.#.#.#.#"),
    str("#...#.#...#.#...#.......#.#.......#.#.#.#.#...#.#.#.#.#.....#...#...........#.#...#.#.........#...#.#"),
    str("#.#.#.#.#.#.#.#.#.#.###.#########.###.#.#.###.###.#####.#####.#.#.#.#.#.#######.#######.#.###########"),
    str("#.#.....#.#.#.#...#...#...#...#.......#.#.#.....#.#.#.....#...#.#.#.#.#...#.#.......#...#.#...#.#...#"),
    str("#####.###.#####.#.#########.###.#.#.#########.#####.###.#.#.#.#.#####.###.#.###.###.#.#.###.#.#.#.###"),
    str("#...#.#...#...#.#...#.....#.....#.#.......#.......#.#...#...#.#.#.#...#...........#.#.#.#...#.......#"),
    str("#.#.###.#####.#.#######.###.#######.#.#.#.#####.###.#######.#.###.#####.#.###.#####.#######.#####.#.#"),
    str("#.#.....#.#.......#.........#.......#.#.#...#.........#.....#...#...#...#.#.#...#.........#...#...#.#"),
    str("###.###.#.#######.#.###.#######.#.#.#.###.#.#######.###.#.#.###.#.#########.#.#.###.#####.#####.###.#"),
    str("#...#...#...#...#...#...#.#.....#.#.#...#.#.........#...#.#...#.#...#.........#...#.#.#.#.#.....#.#.#"),
    str("###.#.###.###.#.###.#####.#######.#.#.###.###.#######.###########.#.#.###.#######.#.#.#.#.###.#.#.###"),
    str("#...#.........#.#...........#.....#.#.#.....#...#...............#.#...#.....#.....#...#.......#.....#"),
    str("#####################################################################################################")
  };
  assert(g[0].size() == w);

  pair<int, int> src = make_pair(1 << 29, 1 << 29);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (g[i][j] == 'L') {
        src = make_pair(i, j);
        g[i][j] = '.';
        i = j = (1 << 28);
      }
    }
  }

  int dot = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      dot += (g[i][j] == '.');
    }
  }

  constexpr lli mod = 998244353;
  vec<str> req;
req.push_back("DDLLUULLRRDDDDRRLLDDDDRRLLDDLLUULLRRDDDDRRLLLLRRUULLRRRRUUUULLLLUUUUUUU");
req.push_back("UUURRLLLLRRDDRRLLDDLLRRDDDDDDLLUUDDDDUURRRRRRUULLUUDDRRUURRUUUULLUURRUU");
req.push_back("UUUUUULLRRDDDDDDDDRRUUDDLLLLUUUUDDLLUULLDDUURRUURRLLLLUURRLLDDLLDDDDUUL");
req.push_back("LUUUURRLLDDDDDDLLUUDDRRDDLLDDRRRRLLDDDDRRLLDDDDDDUULLDDLLDDDDLLDDRRLLDD");
req.push_back("DDLLDDRRLLLLLLUUDDLLDDRRRRLLDDUULLLLDDRRDDRRRRUUDDRRUURRRRUUUUDDRRUURRU");
req.push_back("URRRRUUUUDDLLUUUULLLLUURRRRLLLLDDDDDDRRLLDDLLUUDDRRUUUUUURRRRDDLLRRDDRR");
req.push_back("DDLLLLDDRRDDLLDDRRLLUURRUULLLLDDLLLLLLRRRRDDRRDDRRRRLLDDRRRRUUUUDDDDRRU");
req.push_back("UUUUUUUUUDDDDRRUUUUUUDDRRUUUURRRRLLDDRRRRUURRUURRRRRRRRUUUURRUULLRRDDRR");
req.push_back("UUUUUUDDRRUUUULLRRDDDDRRUUUURRUURRRRUURRLLDDDDUULLLLLLUUUULLUULLRRDDRRD");
req.push_back("DRRUUUURRUURRLLLLRRDDDDRRUURRUUDDLLDDRRRRUUUUUUUULLLLDDUULLUURRRRUULLUU");
req.push_back("LLDDUULLLLUURRLLDDRRRRRRDDRRDDRRRRUUUURRUULLUURRRRRRUUUURRDDRRRRUURRLLL");
req.push_back("LRRDDLLLLUULLLLRRDDLLLLLLUURRLLDDLLRRRRRRRRDDDDUULLDDUULLLLDDRRDDDDRRUU");
req.push_back("RRRRUUUUDDRRUUDDRRDDDDLLDDDDLLRRUUUURRUULLRRUULLLLDDLLDDRRDDLLDDUURRUUL");
req.push_back("LUULLDDDDLLRRUULLUULLLLUUUULLLLRRRRDDDDLLUULLRRDDRRRRDDLLRRDDLLLLLLLLLL");
req.push_back("UUDDLLDDRRLLDDRRRRLLLLUUUURRRRDDRRRRRRDDLLRRDDDDDDRRRRRRUULLLLUURRUUUUL");
req.push_back("LRRDDRRUUDDLLLLRRDDRRLLLLDDRRRRDDDDUULLDDDDRRLLUUUULLLLDDRRLLUULLLLLLDD");
req.push_back("UUUULLLLUUDDRRDDDDLLLLRRDDLLLLLLUUUURRLLDDRRLLDDLLRRRRRRRRRRDDLLDDRRRRU");
req.push_back("UDDRRRRUUUURRRRLLLLDDDDRRDDDDUULLLLRRRRUULLLLLLLLLLDDRRDDRRUUDDRRRRLLDD");
req.push_back("RRDDRRUURRRRUUUUDDRRUUUUUURRUURRRRUULLRRDDLLDDRRLLUULLDDLLDDLLUUDDLLUUL");
req.push_back("LRRDDDDUURRRRDDRRUUDDRRUURRRRUUDDRRLLDDDDDDUUUUUULLDDUULLDDDDRRLLDDRRDD");
req.push_back("UULLLLRRUULLRRUULLLLDDLLLLRRDDRRLLDDRRRRDDRRUUDDRRLLDDUULLLLLLRRRRUULLL");
req.push_back("LUULLDDUULLDDLLDDRRRRLLDDLLRRUULLLLUULLRRDDDDUULLDDDDLLUUUUUUDDLLLLRRRR");
req.push_back("DDLLRRDDDDLLUULLUULLUULLDDDDUUUURRDDDDUURRDDRRDDDDRRRRUURRRRUULLRRDDRRU");
req.push_back("UDDRRUUUURRDDRRUURRDDUULLDDDDRRRRUURRUUDDRRUUUURRUULLRRDDLLDDDDRRUUDDDD");
req.push_back("LLDDRRRRLLDDUULLDDUULLUUDDDDDDRRRRRRUURRRRUULLRRDDRRUUUURRLLLLUUUUDDRRU");
req.push_back("UUUUUUUUURRUUDDLLLLUURRLLLLUURRUUUUUULLUULLLLUUUUUURRUUUULLUUUUDDDDLLRR");
req.push_back("RRDDRRUUUULLUUUUUUUULLDDDDUULLRRUURRDDDDRRUUUUDDRRRRUUUURRRRRRLLLLDDUUL");
req.push_back("LDDLLUULLLLRRRRDDRRDDRRRRUURRRRRRRRUULLLLRRRRDDLLDDRRLLUULLLLDDRRDDRRRR");
req.push_back("DDUULLLLDDDDRRUUDDRRDDUULLLLUUUUUULLUULLDDLLDDRRDDRRUUDDDDLLLLDDRRRRRRR");
req.push_back("RLLDDRRRRLLDDUULLLLDDRRDDDDRRUUDDRRUUUUDDDDDDUULLLLUUUULLDDDDUUUUUURRUU");
req.push_back("LLLLLLDDRRLLDDUULLDDLLLLRRRRUURRUUUURRRRUULLLLRRUULLLLDDUURRUULLLLLLDDR");
req.push_back("RDDUULLDDUULLDDDDRRDDDDRRUUUURRLLDDRRLLDDLLLLDDLLLLUURRLLDDLLDDRRLLLLDD");
req.push_back("DDLLDDUURRUULLRRUURRUULLLLDDUURRRRRRRRDDDDRRUURRRRRRLLDDRRRRUURRUUDDLLD");
req.push_back("DRRLLLLDDRRLLLLRRUULLLLRRUULLLLDDLLLLLLDDUURRRRDDLLRRRRRRDDLLRRRRDDLLDD");
req.push_back("LLDDUULLRRRRUULLLLUUDDLLUUDDRRRRRRRRDDRRUUUURRRRLLDDRRLLUULLDDDDRRLLDDU");
req.push_back("ULLDDLLDDDDDDRRDDDDLLDDUURRUUUULLDDLLUUUUDDLLRRDDDDUURRUUUUUULLLLDDUURR");
req.push_back("RRRRDDRRDDRRDDRRUUDDLLUULLDDDDRRRRRRUUDDRRUURRDDRRUUUULLLLUUUUUUDDLLUUU");
req.push_back("URRLLLLRRDDLLLLRRRRDDDDDDUULLRRUULLRRRRDDRRUUUUUUDDRRUUUUUULLUUDDDDUULL");
req.push_back("UULLDDDDUUUULLRRRRDDDDUURRRRDDDDDDLLDDRRLLDDRRLLLLDDRRRRDDDDLLUULLDDLLD");
req.push_back("DRRDDDDRRUUUURRLLDDRRDDUULLDDDDRRLLDDDDRRUUDDDDDDDDLLDDUULLDDDDRRRRUUDD");
req.push_back("DDUULLLLDDRRLLUULLDDDDRRRRDDRRUUDDDDDDUUUULLDDDDDDLLDDRRRRUUDDDDDDLLDDU");
req.push_back("URRUUUULLLLDDRRLLDDUULLUUUUDDLLRRDDLLDDRRLLUURRRRUUUURRUULLUUDDLLUUDDLL");
req.push_back("UUDDDDLLUUDDRRUURRRRRRUUUUUULLLLDDRRLLUULLDDLLUUUUUUUULLUUDDLLLLRRRRRRD");
req.push_back("DRRLLLLDDUURRDDDDLLLLDDDDUULLLLRRRRUULLRRRRRRDDDDLLUUDDRRUURRUURRUULLRR");
req.push_back("UURRUULLUUUUUURRLLLLLLDDUURRRRDDDDLLUUDDLLRRRRDDLLRRRRUURRRRUUUULLDDLLR");
req.push_back("RUURRUULLLLRRUUUULLDDLLRRUURRUULLUUUULLDDUUUULLDDLLRRUULLLLDDDDRRRRDDRR");
req.push_back("LLDDRRLLUUUULLLLLLDDLLUUDDLLUUUUDDDDRRRRRRDDRRLLDDRRRRDDRRLLUULLDDUULLD");
req.push_back("DDDUULLLLRRRRUULLLLLLDDDDDDRRUURRDDRRLLUULLDDLLUULLDDDDUUUURRUULLLLLLUU");
req.push_back("LLDDUURRUULLLLRRRRRRUURRUULLLLLLDDLLLLUULLUULLDDDDRRDDLLDDRRRRUUDDDDRRU");
req.push_back("UDDDDRRRRRRLLDDUULLLLDDRRLLUUUULLUULLDDLLRRUULLUURRUULLLLLLLLLLDDRRRRLL");
req.push_back("DDDDUUUULLLLLLLLUULLLLDDRRLLUULLDDUULLDDDDRRLLDDRRLLUULLUUDDDDUULLUUDDR");
req.push_back("RRRUUUURRRRRRRRDDRRUURRUURRUUUURRRRUUUULLUULLDDUULLDDUULLDDDDLLLLRRRRUU");
req.push_back("UULLRRRRUULLLLLLLLLLLLUURRRRLLLLLLDDDDLLDDRRRRUUDDDDUULLDDUULLUULLUUUUR");
req.push_back("RUUDDDDUULLDDDDLLRRRRRRUUUURRDDRRRRRRDDDDRRLLLLLLDDRRLLDDLLLLDDRRDDRRUU");
req.push_back("DDLLLLDDUURRUULLUULLLLLLLLLLUUUUUULLRRDDRRUUUURRLLLLUUUUUUDDRRUUUUUUUUR");
req.push_back("RUUUUUUUULLUULLRRDDRRDDRRRRUURRLLLLUUUUUUUUUULLUURRRRRRLLLLLLDDDDUULLUU");
req.push_back("LLDDLLDDUURRUURRDDDDLLDDRRLLLLDDRRRRLLLLDDDDDDLLUULLUUDDLLDDUURRRRDDLLR");
req.push_back("RRRUUUUUULLUULLDDUULLUURRUUUULLLLDDRRLLLLRRUULLRRRRRRDDRRUURRLLDDDDUULL");
req.push_back("DDLLDDLLUUDDDDRRLLUULLUUDDDDDDRRRRLLDDUULLDDLLDDRRRRLLLLLLDDRRLLUULLUUU");
req.push_back("UUUUURRRRLLDDRRLLUULLDDDDLLLLUUUUDDRRLLDDDDDDRRDDDDUULLDDUURRUULLLLDDUU");
req.push_back("RRUUUULLUUUUUURRUUUURRRRRRDDRRUUDDLLDDRRLLUULLDDLLDDUURRUURRUULLLLLLDDR");
req.push_back("RLLLLRRDDLLLLUUUURRLLLLRRDDDDRRDDLLDDUULLUUDDLLUUUUUUDDRRLLDDDDRRRRRRDD");
req.push_back("DDDDUULLDDDDLLDDUULLUUDDDDDDDDUUUUUURRRRUULLUUUULLRRDDLLRRDDRRUURRRRRRR");
req.push_back("RDDLLRRDDDDUURRRRUULLRRRRUULLLLRRRRUUUURRRRRRRRDDDDUURRUURRUURRUURRRRDD");
req.push_back("DDLLRRDDDDRRUUUUUUUURRRRUURRLLDDRRRRLLDDDDRRLLDDRRLLUUUUUULLDDUULLLLDDR");
req.push_back("RDDRRLLDDUUUULLDDDDDDRRRRUUDDLLLLLLLLUUDDRRDDRRDDRRRRUURRLLDDLLDDLLDDUU");
req.push_back("RRUULLLLLLDDRRDDDDUUUULLLLUULLUUDDRRDDLLDDRRLLDDUUUURRRRDDDDLLDDDDRRRRR");
req.push_back("RLLDDRRRRRRUULLUURRUUUUUUDDLLRRDDRRUUUUUUDDRRUUDDLLDDRRRRUUUUUULLRRDDRR");
req.push_back("UUUUUUUUUURRUURRUUDDRRUURRRRRRLLDDLLRRUULLLLDDLLLLLLUURRLLLLLLRRRRDDRRD");
req.push_back("DRRRRDDUULLLLLLLLUUDDDDDDUUUULLRRRRDDDDDDRRLLLLLLLLRRRRRRDDDDDDUULLDDDD");
req.push_back("RRLLLLDDUULLDDDDDDUUUULLLLRRDDLLLLUUDDLLLLRRRRRRDDRRDDDDRRRRLLLLUULLDDU");
req.push_back("ULLLLUULLDDUULLDDDDRRRRLLDDUULLLLDDRRLLDDRRDDDDRRRRDDRRLLLLLLRRRRUULLLL");
req.push_back("LLDDLLRRDDLLRRRRRRRRDDRRLLLLDDRRRRLLDDRRLLUULLDDUULLDDLLRRUULLUULLLLLLD");
req.push_back("DUURRRRDDDDLLDDDDRRUUDDLLLLLLUUDDRRDDRRRRLLLLDDDDRRUUDDDDDDRRUUUUUUDDDD");
req.push_back("DDRRUUUUUUDDDDRRUUUURRUUUURRUULLRRDDDDRRLLUULLDDLLUUUULLDDDDUUUURRDDDDR");
req.push_back("RDDRRRRLLLLDDUULLDDDDDDUULLDDLLLLDDRRRRLLLLDDRRRRLLLLDDRRDDLLRRUULLUULL");
req.push_back("DDDDDDRRRRLLDDDDRRUURRRRUULLRRDDDDRRLLUULLDDUULLDDDDRRRRRRRRUUDDLLLLLLD");
req.push_back("DDDUULLDDDDLLUUDDRRUUUURRUULLLLLLDDRRLLUURRRRUULLUUUULLDDDDLLDDUULLUUUU");
req.push_back("RRLLDDRRLLLLUUUURRUUDDRRLLLLLLRRDDDDDDDDLLRRUUUURRDDDDDDLLLLDDDDDDRRLLD");
req.push_back("DLLDDDDRRUURRRRUUUUDDLLRRDDRRUUUURRUUUULLUUDDDDUULLLLDDRRLLUURRRRRRDDDD");
req.push_back("RRDDRRLLUULLLLDDRRDDUULLDDDDRRLLUULLLLDDRRLLUULLDDDDRRLLUULLDDDDRRDDRRU");
req.push_back("URRRRUURRLLLLRRDDRRRRUUUURRLLDDRRRRUURRUUUURRUUUUDDDDRRRRRRUUUURRUUUURR");
req.push_back("UULLUUUURRLLDDRRLLDDLLRRRRDDLLLLRRDDRRRRLLDDDDUUUULLLLLLUUUUUUUULLUUDDL");
req.push_back("LUUDDRRRRDDRRUUDDLLDDDDLLRRDDLLLLUUDDLLUUDDDDDDLLUUDDDDUULLRRRRUUUURRRR");
req.push_back("RRRRRRDDLLDDRRLLLLUULLRRDDLLRRRRDDDDDDUUUULLDDDDUUUULLLLDDUULLDDLLLLLLR");
req.push_back("RRRRRDDRRRRUUDDLLDDRRRRRRDDRRDDRRRRRRRRUUUUUUDDDDRRLLLLLLUURRLLLLUUUULL");
req.push_back("UURRRRUUUURRRRDDRRUUUUUUUUDDDDDDDDRRUURRLLDDDDRRLLDDRRRRUUUUUUDDRRUUUUU");
req.push_back("ULLUURRRRUULLUURRUULLLLDDLLRRUULLLLUUUUUUUULLUUUUUURRUURRLLLLUUUURRRRLL");
req.push_back("LLDDRRRRLLLLDDRRDDRRDDUULLDDDDRRRRUUUUDDDDLLLLUUUULLDDDDDDRRDDRRUURRRRU");
req.push_back("UUUUUUULLRRDDDDRRUUUUUULLUURRUUDDLLDDRRDDDDRRUUDDLLDDLLDDRRRRUUDDRRLLLL");
req.push_back("LLDDLLDDUULLDDDDUULLDDDDRRLLDDDDLLLLUURRUULLUUUURRLLLLDDDDLLUULLUUDDLLD");
req.push_back("DRRLLDDUUUURRRRDDDDRRLLDDUULLRRUURRUUUULLUUUUUULLUURRUUUUUURRRRDDUULLLL");
req.push_back("DDDDLLRRDDRRRRUULLUUDDRRDDLLDDRRLLDDUUUULLLLLLLLUURRLLDDRRRRDDLLDDLLUUL");
req.push_back("LLLUURRLLDDLLRRRRRRDDDDRRRRLLDDUULLDDLLLLUUDDDDDDRRUURRLLDDRRLLDDRRLLUU");
req.push_back("LLLLLLLLUURRUUUUDDDDRRLLLLDDRRRRRRUUUULLUUUURRRRLLLLDDDDRRRRRRUULLRRUUR");
req.push_back("RUURRRRDDLLRRDDRRRRUUDDLLLLDDRRRRDDRRLLDDRRDDLLDDDDLLUUDDDDRRLLLLUUDDDD");
req.push_back("RRDDRRUUDDLLUULLUURRUURRUURRRRUURRRRRRRRDDLLDDLLLLDDLLRRUULLLLRRRRRRRRR");
req.push_back("RDDDDRRUUUUDDDDRRLLLLUULLLLDDDDLLRRUULLLLDDUURRRRRRDDRRLLDDRRRRUUDDLLDD");
req.push_back("RRRRUUDDRRDDRRUUUUUURRUUUUDDRRUUUUUUUUUUUUUUUUDDRRRRRRUUUUUURRRRLLLLDDD");
req.push_back("DRRLLDDRRRRUUDDLLLLDDLLRRUULLLLLLLLUUDDLLUUUULLUUUUUULLRRDDLLRRDDRRRRDD");
req.push_back("RRUURRUUDDDDRRLLDDRRLLUUUULLDDLLUULLLLLLRRDDDDLLRRUURRDDDDRRRRDDLLRRDDR");
req.push_back("RUUDDLLLLLLUULLUULLRRDDRRDDLLRRRRRRDDLLRRDDRRUUDDLLLLRRDDLLRRDDRRUURRUU");
req.push_back("UUUUDDDDDDLLDDLLDDRRRRUUDDRRUUDDLLDDUULLDDUULLLLLLUULLDDDDLLRRUUUULLUUR");
req.push_back("RUUUUDDRRUUDDLLLLUULLUUUUUUUULLRRDDDDRRDDUULLDDLLUUUUDDDDLLUUUUDDLLDDUU");
req.push_back("RRDDRRRRDDRRDDLLRRRRDDRRLLLLDDRRRRDDRRDDRRLLLLDDLLRRDDRRUUDDRRRRRRUURRU");
req.push_back("UDDDDDDRRUUUUDDRRUUUUDDDDRRUUDDRRUUUUUUUUDDLLUUUUUUDDDDLLUUUULLUUDDDDDD");
req.push_back("UUUULLUUDDDDUURRRRDDDDRRDDLLLLDDUURRRRRRDDLLRRDDDDRRUURRRRDDRRDDRRUUUUD");
req.push_back("DDDDDUULLDDLLUUDDRRUUUULLLLRRUULLLLDDLLDDDDRRUUDDRRUUDDLLLLDDUULLDDDDUU");
req.push_back("LLDDUURRUULLRRRRUUUULLLLDDRRLLUULLDDDDUULLUUUULLLLLLRRRRDDDDUULLLLLLLLD");
req.push_back("DRRLLLLUULLDDLLDDRRRRRRRRRRUURRDDUULLDDLLLLDDRRDDRRUUDDRRRRUUUURRLLDDRR");
req.push_back("RRDDDDRRRRRRDDDDRRRRUURRUURRUUUURRLLDDRRDDDDUUUULLLLUUDDLLUULLDDDDRRLLU");
req.push_back("ULLRRUURRDDRRRRDDLLDDDDRRUUDDRRLLLLUULLLLRRDDLLLLLLUUDDRRUUUULLLLLLDDDD");
req.push_back("RRUUDDLLUUUULLRRUUUULLLLLLRRDDRRLLLLDDRRDDRRDDLLLLRRRRUULLUULLDDLLUUDDL");
req.push_back("LDDRRLLLLRRUULLLLDDLLUULLUUUUDDRRLLDDDDUURRDDRRUURRRRRRRRUUUULLLLDDUULL");
req.push_back("DDLLRRUURRUULLUULLDDDDLLRRUUUULLDDUULLDDUUUURRUULLLLDDUUUULLDDLLLLRRDDR");
req.push_back("RLLDDLLLLDDRRDDRRUURRUURRDDDDUUUULLDDDDDDRRDDUULLUUUULLDDDDDDRRLLUULLDD");
req.push_back("UULLDDLLDDRRRRRRRRRRLLLLLLLLLLLLLLRRRRUURRUURRRRUULLUULLDDLLRRUULLRRUUU");
req.push_back("UUULLDDDDUULLDDUULLDDDDUUUURRRRUULLUULLDDUULLDDDDDDUULLLLDDRRDDRRLLLLRR");
req.push_back("DDLLRRRRDDLLRRRRRRDDLLLLLLDDRRLLUULLUULLDDDDRRLLLLRRUUUUUULLDDUULLDDDDR");
req.push_back("RLLDDUUUUUULLDDDDDDUUUULLDDDDLLLLRRRRUUUULLDDLLLLRRRRUULLRRRRRRUUUULLDD");
req.push_back("UULLDDLLLLDDLLLLDDLLRRUULLLLDDDDRRRRRRUUDDRRLLLLLLLLLLRRUULLUULLLLUULLR");
req.push_back("RDDLLRRRRUUUUUULLUULLUUDDDDDDUUUULLUUDDDDDDDDLLDDDDLLDDRRRRUUUUDDRRLLDD");
req.push_back("RRRRUURRDDUULLDDLLLLLLLLUURRUULLLLUULLDDUURRDDDDDDLLRRUULLRRUURRRRUURRU");
req.push_back("UUULLUUDDDDLLUUUUUUUUDDRRLLLLUUUULLUUUUUUUUDDRRRRLLDDRRDDDDUUUULLDDUUUU");
req.push_back("LLDDDDDDDDUURRDDDDLLRRRRDDLLLLRRRRDDDDDDUULLUULLDDUURRDDRRRRUURRUURRRRD");
req.push_back("DDDUURRUURRUUUULLDDLLUULLRRDDRRUURRUULLUUUUUURRUUUULLRRDDLLRRDDLLDDDDDD");
req.push_back("LLUUUUDDLLUUUURRLLDDDDRRDDLLRRRRRRUURRRRUUUURRRRUUUUUUUUUURRUUUUUUUULLD");
req.push_back("DUULLDDDDDDRRUUDDLLDDDDUUUULLDDUURRUULLRRUULLLLLLRRRRRRUULLLLUULLDDUUUU");
req.push_back("LLDDDDDDUUUULLDDDDLLDDRRDDRRUURRRRDDDDLLDDRRLLUURRUULLRRUULLLLDDLLDDUUU");
req.push_back("ULLDDDDUULLUUDDDDDDRRRRRRUUDDLLDDRRLLDDDDUUUULLDDDDLLDDDDDDDDDDLLUUDDRR");
req.push_back("UUUULLUUDDRRUUUUUURRUUUURRUULLLLLLUUUUUUDDDDLLUULLRRDDLLLLUUUURRUUDDRRU");
req.push_back("UDDLLLLDDDDDDUURRRRRRDDDDRRDDLLDDDDUULLRRUULLRRRRUULLLLUUDDLLUUDDDDDDUU");
req.push_back("LLRRUULLRRRRRRUURRUUUURRUUUULLUUDDLLUUDDRRRRRRUULLRRUURRUULLLLDDLLLLLLU");
req.push_back("ULLDDDDRRLLUULLDDDDUUUURRUULLRRUULLRRRRUURRRRRRUURRUULLRRUUUULLDDLLUUUU");
req.push_back("LLLLDDDDDDRRLLDDUULLLLUUUUUUUUDDDDDDRRLLDDDDRRDDUULLDDUUUURRRRUUUUUULLU");
req.push_back("UUURRLLLLRRDDRRLLDDDDUURRRRRRDDDDDDDDUUUULLUUDDRRRRUURRRRUULLLLUUUURRRR");
req.push_back("LLDDUULLLLUUDDLLUUUUUULLUUUUDDLLLLUURRUUUURRUUUUDDRRLLLLRRDDDDUULLDDLLR");
req.push_back("RDDLLDDDDDDUUUURRRRDDRRDDRRUUUUDDDDRRRRLLDDRRLLUULLLLLLLLUUDDDDLLRRUURR");
req.push_back("RRDDLLRRDDDDUURRRRDDLLRRDDRRRRUURRUURRUULLRRUULLRRUUUULLDDLLUUUUDDDDDDD");
req.push_back("DUUUULLLLRRUULLUUDDRRUUUURRLLUUUURRRRLLLLDDRRLLLLDDLLUULLRRDDDDLLUUDDDD");
  map<str, int> idx;
  for (int i = 0; i < req.size(); ++i) {
    idx[req[i]] = i;
  }
  assert(idx.size() == req.size());

  map<int, pair<lli, lli>> z;

  for (lli loop = 0; ; ++loop) {
    // lli x = xorshift() % 94;
    lli x = 1;
    lli mult = xorshift() % mod;

    const pair<lli, lli> seed = make_pair(x, mult);

    str s;
    for (int _ = 0; _ < 283; ++_) {
      str D = "RDUL";
      s += D[x % 4];
      (x *= mult) %= mod;
    }
    if (idx.count(s)) {
      z[idx[s]] = seed;
      cout << loop << ": " << z.size() << ' ' << req.size() << endl;
    }
    if (z.size() == req.size()) break;
  }
  each (k, z) {
    cout << k << endl;
  }

  return {};
}

int main(int argc, char *argv[])
{
  // abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`|~<space><newline>

  // vec<lli> v = l11();
  // vec<lli> v = l4();

  if (0) {
    vec<lli> v = l11();

    each (i, v) {
      str s;
      lli x = i;
      while (x) {
        s += '!' + (x % 94);
        x /= 94;
      }
      reverse(s.begin(), s.end());
      cout << i << ' ' << s << endl;
    }

    const str table = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n";
    str text = "solve lambdaman11 ";
    each (c, text) cout << (char)(table.find(c) + 33); cout << endl;
  }

  if (1) {
    str t;
    cin >> t;
    cout << t.size() << endl;
    // 2^2×5×7×71
    const int L = 20;
    assert(t.size() % L == 0);
    for (int i = 0; i < t.size(); ++i) {
      cout << t[i];
      if ((i + 1) % L == 0) {
        cout << endl;
      }
    }
  }



  return 0;
}
