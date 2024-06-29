// github.com/Johniel/contests
// johniel/optimize.cpp

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

const int AND = 0;
const int OR = 1;
const int NOT = 2;
const int VAR = 3;

struct C {
  int type;
  C* a;
  C* b;
  str name;

  void comp(void)
  {
    if (type == NOT) {
      // !(a&&b)
      // !a||!b
    }
  }

  void rev(void)
  {

  }
};




str s = "(and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (or (not var19) (not var16)) (or (not var15) (not var10))) (or (or (not var20) var38) var13)) (not var40)) (or (not var21) var19)) (or (or (not var9) var17) (not var25))) (or (not var30) (not var40))) (or (not var1) var20)) var16) (or (or (not var38) var20) (not var7))) (or var26 (not var24))) (or (or (not var18) var41) var22)) (or (or (not var24) var36) var25)) (or (not var31) (not var29))) var16) (or (or (not var38) var20) var7)) (or (not var4) (not var12))) (or (not var36) (not var4))) (or (or (not var30) var40) var23)) (or (not var28) (not var11))) (or var29 (not var9))) (or (not var5) var40)) (or var11 var27)) (or (or var23 var15) var16)) (not var14)) (or (or var37 var29) (not var36))) (or (or (not var9) var17) var25)) (or (or (not var8) var4) (not var41))) (or (or var23 var15) var16)) (not var14)) (or (or (not var9) var17) var25)) (or (or (not var20) var38) var13)) (or var11 (not var27))) (or (not var21) (not var19))) (or (not var9) (not var17))) (or (or (not var4) var12) (not var24))) (or (not var17) var38)) (or (not var39) (not var12))) (or (or (not var32) var14) var15)) (or (not var34) var20)) (or (or (not var15) var10) (not var30))) (or var7 var17)) (or (or var37 var29) var36)) (or (not var20) (not var38))) (or (not var6) var7)) (or var11 var27)) (or (or (not var4) var12) var24)) (or (or var27 var38) (not var17))) (or (or var23 var15) (not var16))) (or (or var26 var24) var39)) (or var37 (not var29))) (or (not var36) var4)) (or (or (not var35) var36) (not var38))) (or (not var6) (not var7))) (or (not var34) (not var20))) (or (or (not var18) var41) var22)) (or (or (not var31) var29) var5)) (or (or (not var35) var36) var38)) (or (or var29 var9) var30)) (not var22)) (or (or (not var19) var16) var40)) var41) (or (or (not var4) var12) var24)) (or (not var18) (not var41))) (or (not var36) var4)) (or (not var34) var20)) (or (or var26 var24) (not var39))) (or (not var28) var11)) (or (or var37 var29) var36)) (or (or (not var8) var4) var41)) (or (not var12) var36)) (or var7 var17)) (or (or (not var31) var29) var5)) (or (not var12) (not var36))) (or (not var33) var20)) (or (not var38) (not var20))) (or var27 (not var38))) (or (or (not var31) var29) (not var5))) (not var22)) (or (not var21) var19)) (or (not var10) var32)) (or (or var29 var9) var30)) (or (or (not var32) var14) (not var15))) (or (or (not var25) var33) var36)) (or var13 var17)) (or (or (not var30) var40) var23)) (or (or (not var15) var10) var30)) (not var40)) (or (not var5) (not var40))) (or (or (not var38) var20) var7)) (or (not var24) (not var36))) (or (or (not var30) var40) (not var23))) (or (not var6) var7)) var41) (or (or var26 var24) var39)) (or (not var1) var20)) (or var13 var17)) (or (or (not var24) var36) var25)) (or (not var32) (not var14))) (or (not var35) (not var36))) (or (not var33) var20)) (or (or (not var25) var33) var36)) (or (or var27 var38) var17)) (or (not var39) var12)) (or (not var17) var38)) (or (or (not var8) var4) var41)) (or (not var5) var40)) (or (not var8) (not var4))) (or (or (not var25) var33) (not var36))) (or (or (not var35) var36) var38)) (or (not var12) var36)) var0) (or (not var28) var11)) (or (or (not var24) var36) (not var25))) (or (or (not var19) var16) (not var40))) (or (or (not var20) var38) (not var13))) (or (or var27 var38) var17)) (or var7 (not var17))) (or (or (not var18) var41) (not var22))) (or (not var10) (not var32))) (or (not var33) (not var20))) (or (not var39) var12)) (or (not var10) var32)) (or (or (not var15) var10) var30)) (or (or (not var19) var16) var40)) (or var13 (not var17))) (or (not var17) (not var38))) (or var23 (not var15))) (or (or var29 var9) (not var30))) var0) (or (not var25) (not var33))) (or (not var1) (not var20))) (or (or (not var32) var14) var15))";

C* rec(void)
{
  while (s.size() && s.front()) {
    s.erase(s.begin());
  }
  while (s.size()) {
    if (s[0] == '(') {
      s.erase(s.begin());
      auto c = rec();
      s.pop_back();
      return c;
    }
    if (s[0] == 'a') {
      s.erase(s.begin()); // a
      s.erase(s.begin()); // n
      s.erase(s.begin()); // d
      auto c = new C();
      c.type = AND;
      c.a = rce();
      b.a = rce();
      return c;
    }

    if (s[0] == 'o') {
      s.erase(s.begin()); // o
      s.erase(s.begin()); // r
      auto c = new C();
      c.type = OR;
      c.a = rce();
      b.a = rce();
      return c;
    }

    if (s[0] == 'n') {
      s.erase(s.begin()); // n
      s.erase(s.begin()); // o
      s.erase(s.begin()); // t
      auto c = new C();
      c.type = NOT;
      c.a = rce();
      return c;
    }

    if (s[0] == 'v') {
      s.erase(s.begin()); // v
      s.erase(s.begin()); // a
      s.erase(s.begin()); // r
      str t;
      while (s[0] != ' ') {
        t += s[0];
        s.erase(s.begin());
      }
      auto c = new C();
      c.type = VAR;
      c.name = t;
      return c;
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
};
