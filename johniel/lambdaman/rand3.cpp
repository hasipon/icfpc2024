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

vec<vec<char>> acc;

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
// abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!"#$%&'()*+,-./:;<=>?@[\]^_`|~<space><newline>
str encode(str text)
{
  const str table = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n";
  // str text = "solve lambdaman11 ";
  str s;
  each (c, text) s += (table.find(c) + 33);
  return s;
}

str encode(lli x)
{
  str s;
  while (x) {
    s += '!' + (x % 94);
    x /= 94;
  }
  reverse(s.begin(), s.end());
  return "I"+s;
}

vec<lli> l17(vec<vec<char>> g, const char srcC, const char dstC, const char landmarkC, const char deathC)
{
  const int w = 100;
  const int h = 141;
  // const int h = g.size();
  // const int w = g.front().size();
  assert(g[0].size() == w);

  pair<int, int> src = make_pair(-(1 << 29), -(1 << 29));
  pair<int, int> dst = make_pair(-(1 << 29), -(1 << 29));
  vec<pair<int, int>> landmarks;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (g[i][j] == srcC) src = make_pair(i, j);
      if (g[i][j] == dstC) dst = make_pair(i, j);
      if (g[i][j] == landmarkC) landmarks.push_back(make_pair(i, j));
    }
  }
  assert(0 <= src.first);
  assert(0 <= dst.first);
  assert(landmarks.size());

  constexpr lli mod = 998244353;

  int mx = 0;
  static lli vis[h][w];
  fill(&vis[0][0], &vis[h - 1][w - 1] + 1, -1);

  for (lli loop = 0; ; ++loop) {
    if ((1 << 29) < loop) {
      loop = 0;
      fill(&vis[0][0], &vis[h - 1][w - 1] + 1, -1);
    }
    auto show = [&] (ostream& os) {
      for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
          if (vis[i][j] == loop) os << "@";
          else os << g[i][j];
        }
        os << ' ' << i << endl;
      }
      return ;
    };
    auto merge = [&] () {
      for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g[i].size(); ++j) {
          if (vis[i][j] == loop) acc[i][j] = '@';
        }
      }
      return ;
    };

    lli x = xorshift() % mod;
    lli mult = xorshift() % mod;
    if (94*94 <= mult) continue;
    const pair<lli, lli> seed = make_pair(x, mult);
    pair<int, int> curr = src;
    assert(g[src.first][src.second] == srcC);
    vis[src.first][src.second] = loop;
    int visited = 0;
    lli mn = 1LL << 60;
    str path;

    vec<lli> rvalues;
    for (int _ = 0; _ < 800000; ++_) {
      rvalues.push_back(x);
      (x *= mult) %= mod;
    }
    reverse(rvalues.begin(), rvalues.end());

    each (x, rvalues) {
      auto [i, j] = curr;
      assert(visited <= landmarks.size());
      (x *= mult) %= mod;
      if (visited == landmarks.size()) setmin(mn, x);
      if (g[i][j] == deathC) break;
      // if (visited == landmarks.size() && curr == dst) break;
      // if (visited == landmarks.size()) break;
      constexpr array<int, 8> di({0, 1, -1, 0, 1, -1, 1, -1});
      constexpr array<int, 8> dj({1, 0, 0, -1, 1, -1, -1, 1});
      const int d = x % 4;
      path += str("RDUL")[d];
      const int ni = i + di[d];
      const int nj = j + dj[d];
      unless (0 <= ni && ni < h) continue;
      unless (0 <= nj && nj < w) continue;
      if (g[ni][nj] != '#') {
        curr = make_pair(ni, nj);
        if (vis[ni][nj] != loop) {
          visited += (g[ni][nj] == landmarkC);
        }
        vis[ni][nj] = loop;
      }
    }

    if (visited == landmarks.size()) {
      cout << "DONE?: " << make_pair(srcC, dstC) << landmarkC << endl;
      cout << "ini, mult, mod, fin" << endl;
      cout << make_pair(seed, mod) << ' ' << mn << endl;
      vis[curr.first][curr.second] = -1;
      g[curr.first][curr.second] = ' ';
      show(cout);
      vec<lli> u({seed.first, seed.second, mod, x});

      clog << "restart?" << endl;
      clog << "DONE: " << make_pair(srcC, dstC) << landmarkC << endl;
      clog << "ini, mult, mod, fin" << endl;
      clog << make_pair(seed, mod) << ' ' << mn << endl;
      each (k, u) clog << k << " " << encode(k) << endl;

      cout << path << endl;
      cout << "restart?" << endl;
      cout << "DONE: " << make_pair(srcC, dstC) << landmarkC << endl;
      cout << "ini, mult, mod, fin" << endl;
      cout << make_pair(seed, mod) << ' ' << mn << endl;
      each (k, u) cout << k << " " << encode(k) << endl;

      exit(1);
      return u;
    }


    if (mx < visited) {
      mx = visited;
      show(clog);
      clog << loop << ": " << seed << endl;
      clog << "info: " << make_pair(srcC, dstC) << landmarkC << ", visited:=" << visited << endl;
    }
  }

  return {};
}

int main(int argc, char *argv[])
{
  const int w = 100;
  const int h = 141;

  vec<vec<char>> g(h, vec<char>(w, '?'));
  assert(cin >> g);

  str header = "solve lambdaman17 ";
  cout << encode(header) << endl;

  while (true) {
    acc = g;

    cout << endl;
    cout << "==================== START ====================" << endl;
    cout << endl;

    {
      vec<lli> v = l17(g, 'A', 'B', '1', '_');
      each (i, v) cout << i << ' ' << encode(i) << endl;
    }
    if (0) {
      vec<lli> v = l17(g, 'B', 'C', '2', '1');
      each (i, v) cout << i << ' ' << encode(i) << endl;
    }

    bool finished = true;
    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        if (acc[i][j] == '.') {
          for (int a = 0; a < h; ++a) {
            for (int b = 0; b < w; ++b) {
              cerr << acc[a][b];
            }
            cerr << ' ' << a << endl;
          }
        }
        finished = finished && (acc[i][j] != '.');
      }
    }
    if (finished) break;
  }

  return 0;
}
