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


#include <boost/multiprecision/cpp_int.hpp>
namespace mp = boost::multiprecision;

std::ostream &operator<<(std::ostream &dest, __int128_t value) {
  std::ostream::sentry s(dest);
  if (s) {
    __uint128_t tmp = value < 0 ? -value : value;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (value < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (dest.rdbuf()->sputn(d, len) != len) {
      dest.setstate(std::ios_base::badbit);
    }
  }
  return dest;
}

str __int128_to_str(__int128_t value)
{
  str s;
  bool neg = value < 0;
  while (value) {
    s += '0' + (value % 10);
    value /= 10;
  }
  reverse(s.begin(), s.end());
  if (neg) s = "-" + s;
  return s;
}

__int128 parse(string &s) {
  __int128 ret = 0;
  for (int i = 0; i < s.length(); i++)
    if ('0' <= s[i] && s[i] <= '9')
      ret = 10 * ret + s[i] - '0';
  return ret;
}

const str table = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n";
map<char, int> inv;

str translate(str s)
{
  str t;
  each (c, s) t += table.at(c - 33);
  return t;
}

str base94(str s)
{
  mp::cpp_int x = 0;
  each (c, s) x = x * 94 + (c - 33);
  return x.str();
}

map<str, int> var_pool;

vec<str> tokenize(str s)
{
  istringstream iss(s);
  vec<str> v;
  for (str t; iss >> t; ) {
    if (t.empty()) continue;

    if (t.front() == 'I') {
      t.erase(t.begin());
      v.push_back("I");
      v.push_back(t);
      continue;
    }

    if (t.front() == 'S') {
      t.erase(t.begin());
      v.push_back("S");
      v.push_back(translate(t));
      continue;
    }

    if (t.front() == 'U') {
      t.erase(t.begin());
      v.push_back("U");
      v.push_back(t);
      continue;
    }

    if (t.front() == 'B') {
      t.erase(t.begin());
      v.push_back("B");
      v.push_back(t);
      continue;
    }

    if (t.front() == 'L') {
      t.erase(t.begin());
      v.push_back("L");
      unless (var_pool.count(t)) var_pool[t] = var_pool.size();
      v.push_back("var" + to_string(var_pool[t]));
      continue;
    }

    if (t.front() == 'v') {
      t.erase(t.begin());
      v.push_back("v");
      unless (var_pool.count(t)) var_pool[t] = var_pool.size();
      v.push_back("var" + to_string(var_pool[t]));
      continue;
    }

    v.push_back(t);
  }
  return v;
}

queue<str> q;
void eval(void)
{
  const str indicator = q.front(); q.pop();
  // if (q.size()) cerr << indicator << ' ' << q.front() << endl;
  if (0) {
  } else if (indicator == "T") {
    cout << "(T)";
  } else if (indicator == "F") {
    cout << "(F)";
  } else if (indicator == "I") {
    str v = q.front(); q.pop();
    // cout << "(bigint-string-to-bigint \"" << base94(v) << "\")";
    cout << base94(v) << "\n";
  } else if (indicator == "S") {
    str msg = q.front(); q.pop();
    str s;
    each (c, msg) {
      if (c == '\\') {
        s += "\\";
        continue;
      }
      if (c == '\'') {
        s += "\\\'";
        continue;
      }
      if (c == '\"') {
        s += "\\\"";
        continue;
      }
      s += c;
    }
    cout << "\"" << s << "\"" << endl;
  } else if (indicator == "U") {
    str op = q.front(); q.pop();
    if (op == "-") {
      cout << "(- "; eval(); cout << ")";
    }
    if (op == "!") {
      cout << "(not ";
      eval();
      cout << ")";
    }
    if (op == "#") { // string to int
      cout << "(string-to-int ";  eval(); cout << ")" << endl;
    }
    if (op == "$") {
      // cout << "(bigint-to-string ";  eval(); cout << ")" << endl;
      cout << "(number-to-string ";  eval(); cout << ")" << endl;
    }
  } else if (indicator == "B") {
    str op = q.front(); q.pop();
    if (op == "+") {
      // cout << "(bigint-add "; eval(); cout << " "; eval(); cout << ")";
      cout << "(+ "; eval(); cout << " "; eval(); cout << ")";
    }
    if (op == "-") {
      // cout << "(bigint-subtract "; eval(); cout << " "; eval(); cout << ")";
      cout << "(- "; eval(); cout << " "; eval(); cout << ")";
    }
    if (op == "*") {
      cout << "(* "; eval(); cout << " "; eval(); cout << ")";
    }
    if (op == "/") {
      // cout << "(bigint-divide "; eval(); cout << " "; eval(); cout << ")";
      cout << "(/ "; eval(); cout << " "; eval(); cout << ")";
    }
    if (op == "%") {
      cout << "(% ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == "<") {
      cout << "(< ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == ">") {
      cout << "(> ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == "=") {
      cout << "(= ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == "|") {
      cout << "(or ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == "&") {
      cout << "(and ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == ".") {
      cout << "(s-concat ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == "T") {
      cout << "(take ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == "D") {
      cout << "(drop ";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }
    if (op == "$") {
      cout << "(funcall ";
      // cout << "(";
      eval();
      cout << " ";
      eval();
      cout << ")";
    }

  } else if (indicator == "?") {
    cout << "(if ";
    eval();
    cout << "\n";
    eval();
    cout << "\n";
    eval();
    cout << ")";

  } else if (indicator == "L") {
    str var = q.front(); q.pop();
    cout << "(lambda (" << var << ") " << endl;
    eval();
    cout << ")";

  } else if (indicator == "v") {
    str var = q.front(); q.pop();
    cout << var << endl;
  }
  return ;
}



int main(int argc, char *argv[])
{
  cout << "(setq lexical-binding t)" << endl;
  cout << "(setq max-specpdl-size 10000)" << endl;
  cout << "(setq max-lisp-eval-depth 10000)" << endl;
  cout << "(define-obsolete-function-alias \'string-to-int \'string-to-number \"22.1\")" << endl;
  cout << "(add-to-list \'load-path \"./site-lisp/bigint/\")" << endl;
  cout << "(add-to-list \'load-path \"./site-lisp/s\")" << endl;
  cout << "(require \'s)" << endl;
  cout << "(require \'bigint)" << endl;
  cout << "(defun T () t)" << endl;
  cout << "(defun F () nil)" << endl;
  cout << "(defalias 'take 's-left  ))" << endl;
  cout << "(defalias 'drop 's-right ))" << endl;

  // str code = "B$ B$ L# L$ v# B. SB%,,/ S}Q/2,$_ IK";
  str efficiency1 = "B$ L! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! B$ v! I\" L! B+ B+ v! v! B+ v! v!";
  str efficiency2 = "B+ I7c B* B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B= v% I! I\" B+ I\" B$ v$ B- v% I\" I\":c1+0 I!";
  str efficiency3 = "B+ I7c B* B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B= v% I! I\" B+ I\" B$ v$ B- v% I\" I\":c1+0 I\"";

  str efficiency4 = "B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B< v% I# I\" B+ B$ v$ B- v% I\" B$ v$ B- v% I# II";

  str lambdaman10 = "B. SF B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L\" L# ? B= v# I;Y S B. ? B= B% v# IS I! S~ S B. ? B= B% v# I, I! Sa Sl B$ v\" B+ v# I\" I\"";
  str lambdaman6 = "B. SF B$ B$ L\" B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L# ? B= v# I\" v\" B. v\" B$ v$ B- v# I\" Sl I#,";
  str lambdaman9 = "B$ L+ B. B. SF B$ B$ v+ Sl IR B$ B$ v+ B. S~ B$ B$ v+ Sl IS IR L\" B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L# ? B= v# I\" v\" B. v\" B$ v$ B- v# I\"";

  str efficiency5 = "B$ L\' B$ L( B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B& B> v% I\"41= B& B$ v\' v% B$ v( B+ v% I\" v% B$ v$ B+ v% I\" I# B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B= v% I\" T ? B= B% v% I# I\" F B$ v$ B/ v% I# L& B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B= v% v& T ? B= B% v& v% I! F B$ v$ B+ v% I\" I#";

  str efficiency6 = "B$ L\' B$ L( B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B& B> v% I? B$ v\' B$ v( v% v% B$ v$ B+ v% I\" I# B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B< v% I# I\" B+ B$ v$ B- v% I\" B$ v$ B- v% I# L& B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B= v% v& T ? B= B% v& v% I! F B$ v$ B+ v% I\" I#";

  str efficiency12 = "B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% B$ B$ L\" L# ? B< v\" v# v\" v# v% B+ I\" ? B> v% I# B$ B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L& L' L( ? B= v' v% v( B$ B$ v& B+ v' I\" ? B> B$ v$ v' B- v' I\" ? B= B% v% v' I! B* B/ v( B$ v$ v' B- B$ v$ v' I\" v( v( I# v% v% I\"Ndb";

  str efficiency8 ="B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# LK LJ B$ L\" B$ L# B$ L$ B$ L% B$ L& B$ L\' B$ L( B$ L) B$ L* B$ L+ B$ L, B$ L- B$ L. B$ L/ B$ L0 B$ L1 B$ L2 B$ L3 B$ L4 B$ L5 B$ L6 B$ L7 B$ L8 B$ L9 B$ L: B$ L; B$ L< B$ L= B$ L> B$ L? B$ L@ B$ LA B$ LB B$ LC B$ LD B$ LE B$ LF B$ LG B$ LH B$ LI ? B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B| U! v3 U! v0 B| U! v/ U! v* B| B| U! v4 vF v- U! vH B| U! v5 v3 B| B| U! v) v1 U! v9 B| U! v> U! vH B| U! v# v4 v0 B| B| U! vF v4 U! v\' B| v: U! v8 B| B| U! v2 vI v6 B| B| U! v8 vD v9 B| U! v? U! v= v0 B| B| U! vF v4 v\' B| U! v$ U! v, B| U! vD U! v$ B| B| U! v> vH v7 B| U! v< U! v+ B| v= U! v) B| U! v% vH B| v+ v; B| B| v7 v/ v0 U! v. B| B| vE v= U! vD B| B| U! v) v1 v9 B| B| U! v( v$ U! vI B| B| v7 v/ v0 U! v. B| B| U! v) v1 v9 B| B| U! v4 vF v- B| v+ U! v; B| U! v5 U! v3 B| U! v) U! v1 B| B| U! v$ v, U! v8 B| U! v1 vF B| U! vG U! v, B| B| U! v@ v. v/ B| U! vB v4 B| B| U! v/ v* U! v> B| v\' v1 B| B| vE v= vD B| U! v4 U! vF B| U! v& v\' B| v+ v; B| B| U! v$ v, v8 B| B| v; vF U! v1 B| B| v7 v/ U! v0 B| B| v: v8 vG B| vE U! v= B| U! vD v$ B| B| U! vC vD U! vF B| U! v& U! v\' B| U! vB U! v4 B| B| U! v2 vI v6 B| B| U! v? v= v% B| B| U! vC vD vF B| B| v= v) v> U! v6 B| B| U! v3 v0 vH vI B| B| U! v$ v, v8 B| U! v2 U! vI B| U! vD v$ B| U! vB v4 B| B| v: v8 U! vG B| U! v< v+ B| B| vE v= vD B| B| U! v( v$ vI B| U! v, vD B| v\' v1 B| B| U! v? v= v% B| U! v, U! vD B| U! vA v4 B| U! vF U! v4 B| v; U! vF B| B| U! v? v= U! v% U! v6 B| U! v5 v3 B| U! v* v@ B| B| v= v) v> B| B| U! v@ v. U! v/ B| B| U! v9 vA vD B| v- v1 B| B| U! v> vH v7 B| B| U! v/ v* v> U! vH B| U! v% U! vH B| B| U! vF v4 v\' B| U! v8 U! vD B| B| U! v> vH U! v7 B| U! v& v\' vI B| B| v: v8 vG B| U! v# v4 B| v- v1 B| B| U! v8 vD v9 B| U! v@ U! v. B| U! vC U! vD B| U! vA v4 B| B| U! v9 vA vD B| B| v; vF v1 B| U! vG v, B| U! v1 vF B| B| U! v( v$ vI B| U! v% vH B| U! v( U! v$ B| B| U! v9 vA U! vD B| B| U! vC vD vF B| U! v, vD v\" B| U! v< v+ B| B| U! v8 vD U! v9 B| B| U! v3 v0 U! vH B| B| U! v4 vF U! v- B| B| v; vF v1 B| v\' U! v1 B| B| U! v2 vI U! v6 B| U! v* U! v@ B| U! vA U! v4 B| U! vG v, B| U! v* v@ B| B| U! v/ v* v> B| B| U! v3 v0 vH B| v- U! v1 B| U! v1 U! vF B| v7 U! v/ B| B| v= v) U! v> v\" B| U! v9 U! vA B| U! v# U! v4 B| B| U! v@ v. v/ vJ B$ vK B+ vJ I\" B< I! B% B/ vJ IkvEaR3 I# B< I! B% B/ vJ IFKbA9Y I# B< I! B% B/ vJ I3eA`-= I# B< I! B% B/ vJ I*C1@V/ I# B< I! B% B/ vJ I%a)0jW I# B< I! B% B/ vJ I#A%(tk I# B< I! B% B/ vJ I\"1#$yu I# B< I! B% B/ vJ IX\"\"|K I# B< I! B% B/ vJ I<PP}e I# B< I! B% B/ vJ I.gg~C I# B< I! B% B/ vJ I\'sDOa I# B< I! B% B/ vJ I$J2gA I# B< I! B% B/ vJ I\"dXs1 I# B< I! B% B/ vJ Iqky) I# B< I! B% B/ vJ IIFM% I# B< I! B% B/ vJ I53f# I# B< I! B% B/ vJ I+*CQ I# B< I! B% B/ vJ I&%a9 I# B< I! B% B/ vJ I#RA- I# B< I! B% B/ vJ I\"9`\' I# B< I! B% B/ vJ I\\@S I# B< I! B% B/ vJ I>_i I# B< I! B% B/ vJ I/oE I# B< I! B% B/ vJ I(H3 I# B< I! B% B/ vJ I$cY I# B< I! B% B/ vJ I\"q= I# B< I! B% B/ vJ Ix/ I# B< I! B% B/ vJ ILW I# B< I! B% B/ vJ I6k I# B< I! B% B/ vJ I+u I# B< I! B% B/ vJ I&K I# B< I! B% B/ vJ I#e I# B< I! B% B/ vJ I\"C I# B< I! B% B/ vJ Ia I# B< I! B% B/ vJ IA I# B< I! B% B/ vJ I1 I# B< I! B% B/ vJ I) I# B< I! B% B/ vJ I% I# B< I! B% B/ vJ I# I# B< I! B% B/ vJ I\" I# I\"";
  str efficiency7 ="B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# LK LJ B$ L\" B$ L# B$ L$ B$ L% B$ L& B$ L\' B$ L( B$ L) B$ L* B$ L+ B$ L, B$ L- B$ L. B$ L/ B$ L0 B$ L1 B$ L2 B$ L3 B$ L4 B$ L5 B$ L6 B$ L7 B$ L8 B$ L9 B$ L: B$ L; B$ L< B$ L= B$ L> B$ L? B$ L@ B$ LA B$ LB B$ LC B$ LD B$ LE B$ LF B$ LG B$ LH B$ LI ? B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B& B| U! v3 U! v0 B| U! v/ U! v* B| B| U! v4 vF v- U! vH B| U! v5 v3 B| B| U! v) v1 U! v9 B| U! v> U! vH B| U! v# v4 v0 B| B| U! vF v4 U! v\' B| v: U! v8 B| B| U! v2 vI v6 B| B| U! v8 vD v9 B| U! v? U! v= v0 B| B| U! vF v4 v\' B| U! v$ U! v, B| U! vD U! v$ B| B| U! v> vH v7 B| U! v< U! v+ B| v= U! v) B| U! v% vH B| v+ v; B| B| v7 v/ v0 U! v. B| B| vE v= U! vD B| B| U! v) v1 v9 B| B| U! v( v$ U! vI B| B| v7 v/ v0 U! v. B| B| U! v) v1 v9 B| B| U! v4 vF v- B| v+ U! v; B| U! v5 U! v3 B| U! v) U! v1 B| B| U! v$ v, U! v8 B| U! v1 vF B| U! vG U! v, B| B| U! v@ v. v/ B| U! vB v4 B| B| U! v/ v* U! v> B| v\' v1 B| B| vE v= vD B| U! v4 U! vF B| U! v& v\' B| v+ v; B| B| U! v$ v, v8 B| B| v; vF U! v1 B| B| v7 v/ U! v0 B| B| v: v8 vG B| vE U! v= B| U! vD v$ B| B| U! vC vD U! vF B| U! v& U! v\' B| U! vB U! v4 B| B| U! v2 vI v6 B| B| U! v? v= v% B| B| U! vC vD vF B| B| v= v) v> U! v6 B| B| U! v3 v0 vH vI B| B| U! v$ v, v8 B| U! v2 U! vI B| U! vD v$ B| U! vB v4 B| B| v: v8 U! vG B| U! v< v+ B| B| vE v= vD B| B| U! v( v$ vI B| U! v, vD B| v\' v1 B| B| U! v? v= v% B| U! v, U! vD B| U! vA v4 B| U! vF U! v4 B| v; U! vF B| B| U! v? v= U! v% U! v6 B| U! v5 v3 B| U! v* v@ B| B| v= v) v> B| B| U! v@ v. U! v/ B| B| U! v9 vA vD B| v- v1 B| B| U! v> vH v7 B| B| U! v/ v* v> U! vH B| U! v% U! vH B| B| U! vF v4 v\' B| U! v8 U! vD B| B| U! v> vH U! v7 B| U! v& v\' vI B| B| v: v8 vG B| U! v# v4 B| v- v1 B| B| U! v8 vD v9 B| U! v@ U! v. B| U! vC U! vD B| U! vA v4 B| B| U! v9 vA vD B| B| v; vF v1 B| U! vG v, B| U! v1 vF B| B| U! v( v$ vI B| U! v% vH B| U! v( U! v$ B| B| U! v9 vA U! vD B| B| U! vC vD vF B| U! v, vD v\" B| U! v< v+ B| B| U! v8 vD U! v9 B| B| U! v3 v0 U! vH B| B| U! v4 vF U! v- B| B| v; vF v1 B| v\' U! v1 B| B| U! v2 vI U! v6 B| U! v* U! v@ B| U! vA U! v4 B| U! vG v, B| U! v* v@ B| B| U! v/ v* v> B| B| U! v3 v0 vH B| v- U! v1 B| U! v1 U! vF B| v7 U! v/ B| B| v= v) U! v> v\" B| U! v9 U! vA B| U! v# U! v4 B| B| U! v@ v. v/ vJ B$ vK B+ vJ I\" B< I! B% B/ vJ IkvEaR3 I# B< I! B% B/ vJ IFKbA9Y I# B< I! B% B/ vJ I3eA`-= I# B< I! B% B/ vJ I*C1@V/ I# B< I! B% B/ vJ I%a)0jW I# B< I! B% B/ vJ I#A%(tk I# B< I! B% B/ vJ I\"1#$yu I# B< I! B% B/ vJ IX\"\"|K I# B< I! B% B/ vJ I<PP}e I# B< I! B% B/ vJ I.gg~C I# B< I! B% B/ vJ I\'sDOa I# B< I! B% B/ vJ I$J2gA I# B< I! B% B/ vJ I\"dXs1 I# B< I! B% B/ vJ Iqky) I# B< I! B% B/ vJ IIFM% I# B< I! B% B/ vJ I53f# I# B< I! B% B/ vJ I+*CQ I# B< I! B% B/ vJ I&%a9 I# B< I! B% B/ vJ I#RA- I# B< I! B% B/ vJ I\"9`\' I# B< I! B% B/ vJ I\\@S I# B< I! B% B/ vJ I>_i I# B< I! B% B/ vJ I/oE I# B< I! B% B/ vJ I(H3 I# B< I! B% B/ vJ I$cY I# B< I! B% B/ vJ I\"q= I# B< I! B% B/ vJ Ix/ I# B< I! B% B/ vJ ILW I# B< I! B% B/ vJ I6k I# B< I! B% B/ vJ I+u I# B< I! B% B/ vJ I&K I# B< I! B% B/ vJ I#e I# B< I! B% B/ vJ I\"C I# B< I! B% B/ vJ Ia I# B< I! B% B/ vJ IA I# B< I! B% B/ vJ I1 I# B< I! B% B/ vJ I) I# B< I! B% B/ vJ I% I# B< I! B% B/ vJ I# I# B< I! B% B/ vJ I\" I# I\"";

  str efficiency13 = "B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L$ L% ? B= v% S I! B+ I\" B$ v$ BD I\" v% B$ L# B. B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# B$ v# S.! S(%9*5$% L\" B. v\" v\"";

  str lambdaman21 = "B$ B$ L\" B$ L# B$ v\" B$ v# v# L# B$ v\" B$ v# v# L\" L# ? B= v# I! Sllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll B. B$ v\" B/ v# I% BT I\" BD B% v# I% Sl~aF B+ IX[d}#i\'kh80Ou!-/&+A\"CWcjm7lbk\\Zas8A\\/.Om*0(u@D\'\'x&S&\\R}%+i,Y6{v?[SiV]]$:~&n$C}8$s,nI~^56aylV\'B[q0G,B[E`!UqL0;iP4Pa<h$\\fV?Bn#X{%Lt8b&)hjQyh8C$kw}\\-Y+7E4!/0c=T`RuV,>6Cn_jMB>7[Hg7%\\PgR&XrDaRD)Bsp|b!pQb&eb1?{$^)Ly*bEX=rMaddCc(]so`-Y#9x?}aH]dNQ/o:n5Y9y!#K-8HB/w$?N\'*EMN_&^]/Rb!pQN1x+^Q#n3](wKEOZQL.opf]G)4[No+\'gd9.R4A?,tw_NHr2jc*Po?]5(/:bJnDN3K<.|hsFeSqg`c@x}Z^[1bo%,7D]XrF&yHyw0mh:|HOGs{uK%mY34Cz*?jiS%idA-i2#b9@obB}j_[zj1nMdeBCga{\"ej*\'bIpBc!K5$)y\'N\\,AnMk367&j&stq{NQS~1_>/=twpe<m5un~Wa5[&A&g,aS-[(`_K8:DX\'o\\E;V}>i51Csq-rLWWn4n%Y?Al?|Oy3*5ko!h0dQ4\\9FRK5inJjBn3**]}yI\'O@)QB/yq\\l(q*)u*KvM9FwW}mVMrn>Ae-JU*X?]L1+G^IO?g\\^Hqrb~:N}y1~V\\C;QC}ij+KVlRi<7%oQ#N/<vwX*/NH0<<|hv8$G5-a,H%\'\\s8|h83q3uh$N[o~0=^.~Ma,m?*,kR_Q03:=?d.kQP8mIz*UqMIsST1m1Ea(XS:CmMYe<RK4|_A#N~}/c)=[j$cy.IltzacZV1\\!+=fQh$#ve~xXhZP1P0+4j~GJF:E0A2NAgeysaGbieUP\\4Uak\\j61JO^45k[ji@Nt8[KV3gnt_./i!;d6Yopq`He.%uD.q2Uli\"yKsu$oCVop~[u+>f[AAFPRXWcN0X`?x<)N#;~{sQ:>Y:YE`uf!8Z]|0;V\'[{^siNQ,qG{wyZfQ[c0;/HvTq*E^!;_4S1acWF,O4}VK&,=`Re+AxNOv)\')83J,/FL-+F\\Zu|;^X?k\\*#\'\\7rKH\\*:yj\\]9$mrlDN^\"mT.\")8cCo5sUZLD,NDzL$R_@])`z~DQmra[-mVG9c$ssUF(04h1sU|mWp=wXXUXr9$=7WcZ0d=[ZB6%ieqf#ApLW#qfDs+Nf%o/1BB-:I(hqQTy,!$QrzNf%`u<iSizU$yU;X<AMt_1Faz\\RT)_DGH6y\'Y]rQW{UN[+jgmW^`,EW*N.0oEinfh,#UQYwRq5i,Yc7X8DODerY*Nh,oJFh*_e^p(3g70,6l&rMcYNZM{_?s!EOm<cZJKpI2h]Q-48LDqWV72,WrF&pB.u)q:`b)1O|(sG~SJ%QC!-v0[C`2lPSd7\'{^k7[[iJ=e70;WVknl&;D\\-7X_7sH57%L9a,r54Y7$\"-C(lbr+0:YeI9N989zQbi}wa%Ds^N4HppLIw1Z@0)mnF6jgt{CaP#OwmzZr^kO~.\\Ke.{{Lwq,rI-*{r0]){H77t1V9:IREeG,DL89%[D!lOpMo4F}p!+$9;_|=2Ym\'.i6(e@LL{[PQQU#~fZI(.+!o%#)d1MG3,?i!@tPz;XY>pJXKWhxieM_&lgB9s><<Df68DhJ/,g>Ss42-DFR#;mz{y0=\\WL05.lCSDyY?~:?<g_2ZQAl9lnAZ\\V^mFU\\%ZjVh(twE%~\"[w\\}T2BCYNIN3>r_3`rm#,~Osq?,p2j/tM}[D^1G,<a;Sr-u5y9k!*Kn!5?&a5--xm`P8@7\\^\'jqy%{dt#ViilbyUlllKU&Z@,Y$UNs<rhO>8HK1LSyhOMkCX-ZJYXk7=~8i2r]M1I;Ep?y2*U{d[76`)/L*\\%Sf@CHG2G%>tl!`PYYzZA(ymVfx0ZVPC8/kHn{[DW=\\~mp#D5[4%)Q\\Ew{1.A55MS}Tk$\\qV~Bndwt/\\a\"\"/i.;x4fQZprYtlmn;Wv>yf~CdF<_G[P[,RBBDn:k<Y.Vuezhe,=7x1Lp#8J[1xAu3SO]o6<VS/+fGq}sA&ZXC1W|!,v!HSglQ<KOA1_vJKqOZqV8q](}^B/8o?5BpHkKEM%)Qgq\\\"ml.x3*0yp&oT\"|I^u<d(?rb]0]\'06|wnLe@S^%Gi_%%KX4Fy2?t8J4iZ^P?j|A#LQ(>au2VA>%&]W]\"I<0T,Sj2.JG%m9qmJM6kF_c|jry)a^K:M$Kz3Z\\HF(>FDP.m@-3x58MBpMa%):DS^&1?GP[OfK);:{Dos.SWV1?C}b60Q70_a`$\"-vcs.J()PF@KX;^i[UF5W|^z9aLK}OKSu?5W)d_L$9J\"\"n\'L9UcQ3F\'Jc`-rYY3~vJQ1)lp]_4W;wYF[j?4XV%s6pb^\"vRi54h3>y)P$(~pc4-IcBlx:5NyUM;]-=xvsZr,p3#L3tC:%Bimsn#**lkRlU@E?\"?agZ^1SkV\\}N/t#eqnYO$/#J5c<{;NSn6o**?i(_O2K:Q!C]W2DbKo5YYnBONP]xJsov$iS~q\\A}u(W\'SbNF#[W^$JUtF01uwM-|WTmM5|||_EG4LV+|M1UB;]07aC^{~Eu\\S.BCq@\":>P|kz\"R9emg:;]VNy6KeKQg$JasS7lRV+f{nXB\'`@*78r\"Jn_UhSSawt$X;][y+]CI&4d]!7M`,j,CcuV}Y]Da1E.uscD9<T7I4F!O<`hh~D)baHQUyS:cp#T}WIzpKp:/?zX&u-3#][2B&^P!rQ.KR!Xd;5q2$-j\\^G1;cjTknFJQJ}(C0U~LmTwH\"lqPDHPpF.0z+IaF{JsH@p|EXZwE8K-T/hn{do-D!O6%zDhkvQl/9CA#CJa+|,W{Vb8,\\$KeTq4BJm|^0>fE13sp|[zDg;/^I,-bZ_3aI(6}t<GB?O4BAy?9n^tix]k(V`U3&d^xx~^RJUP{1B<uyRl`<\'@\\}Voged{Dxxjmu#AK\"~={dbBh+&>eFNf@|~\'N@Rf]\"<q\'AKT%fbb]+H/w[W<#uY_D)&@6\'Iy8H*?\'>L8EaPB,l{DsrV2JkS18g>I&E&db12KGC%T+HajZ|]S@a=8);7yVD>P*|!~\'NFrx$%#L=:$p~d}#/EvW7g*I&-B,9iI/~{,mFO%v*x+di79&Eq622xh1XdPO#<(rdfR5+k\"%p:k6s[d\'^=s;%m+p\'kbS,~~g~J9{CadPQ\'\"(\\fu\"ySe$VF_RYo&ew%,nun(#$\'3Q?$gB$9cz*KM39/tdKf1Tb0e`]j$5rZa_~A6o]k~0=L]F}-+W{CLQ\'<l}&;+:jE$A^4:B#zW~xu,1m&ccJ`x:1]q,HVB\"JZb?W_?7{;?\\pVj_w7WDfR7fJk\'M*:kua=g?Zg&<*_c9\\,-|>|a4{UwL&S*\"QHbR;T\'\\mGTL4_$}J*Hvu(fli=B7u)8=+{c|}+l3BW0WS\\Xwu1!#QNm:Y=jl-+08`J:\'C6m-Tij!,9uMO<7LFy\\\'4*Af+c>~Crf}<gfS|#,q%HU=V_CgJn$gAn]f#GK4NPtD{KU8pw}6vzQaLY-%;,|ShUev<AeSD}fd?=0]>0\\:{)8Bu>0!cpXgX\'i)Yu:1J63BaW%w|D:Jqp{N#D?J?IRgmebL=nQXDcs9?\\(c-|[|nq2Y&ppe%5vEW8jXlXctDK=<6e(P9gFr;n};\'?1wIHXl`<6Rs:YX*5mDF0XzMc%_sQ=W|*wx:g&gu)FH:2*MQ;aD;@CJ7]%1Yd~\"kx5t#|*EAx{2Htb:y\"X#m$u,=;{qY7\\st,aH3v;T$7tI\\Y?mx:Q;{32GPTF?\'1#H\'U6q~@Co=eP!gcgH/1_R]s5H?G{\"f4lDlKc_Z;]eG4,{8>VwjCm[oR@\\^-c?4g@1c{g>(ImPn,h)%r4]C}?+X;2p)wE@ZZbb0gJE/uJHvZR-cW;eEWqNBax[E*Cf>2cQG89:b*~&^l[;-bmUYlCEU32Vc%G+G-srTl\")Ra*fJ.Zwic@m[maCG&S0}Jd2U\'oiY>ajOrn[SPchL:>+(o]|}6<a9L?\\OR;dV2Nw<GC+md@0SL8UF3UqbsvWEE}p\'hNv\"[DirMJ1;r3>nf?NRm<gAgEQzmV:6i*fVE}cek\\s7\'(MeG\\.LF&lCBo05vJO\"L@e^LN?0x0v(]v9O,gb>+@AK9^%rgd5meMs&8fV*6CQ^!aZS$;ZR/2^\\aRwRo$2Q(IT;es1\"`l*e,a]e/LImXq*^Sh_CXVN2_GGgD9e\"X^|\\Ap1}ZSL%8pz6\"=1@`{;,z`-p98wt\"y7:%xh|3M>f~7rsH0wv;3)}w\\ggpY@i;l]7z@cbiL\'L,d/!`jK>(Fu[`Wx5rwX,yfm>}LDA]}=GX^a<Vt`m)2\'ZVBV@\\Yx~@p(.6sBX%|4(bG7k(\"*0~TddX-1twD/4$_5a0S%5:{\"j7Odn3{z%,jU3y}P=xnRzOeQ&_8n|X:`,ecwRF=`\'kxW`jFYg:GU{z!s~rA/1Ln\\zlB\".H&,zf.W6!6K>dClkBp%KwE3u7mT#LZ!ja#J2\\-pYgkr\'Q2\'+I%eXTr::ii?S]QxLPK8Pg\'p9@f\\JmyUyfnM@6V3\'F*?(q4R~ep#K|\"Gky*lo2m_UV;]LhN_*T7lJv,\"[|GYUu]vuJhY[N)`Tb}O5~whK{WI:5r!2EEBNvY2wBkuAa\"XQ`Z-mbYisZiiN*&cLWCOv<6tPFP?9C?zFz21AMy*,*fi;E[QyFA$Sr4awYdg>D^1/Zl_6Ynn7sKlF)V\\ZVR^<|F3&Tq6D,)Cys<I^a|_;fnO;(Yjd\'iF2w(TQNKfT)<A1ccDN1B\'6hAjYB}d\"rT4(@saQ&C~s&&W&yF4xOQ15siOPNHWwgJ?$Y[AJn.5`KBaiJa.{&w!q4@_4gkwJEf0MK2h_n[*`\'|K#Td=Pxq\\O`b:oSGu3`7Q?o{eTlaac2klRLAx&|P_ni7Epk{Cq$Vf2e9~<Q\"lv>/k62MU0,2&3+1,?50$0c?S^wv&(dg#aiPS4U/@WhBtI]KzXF0149q4zRuxD}-9r>\\nf]wl9#hk\'!\\#qukcc=Hgq7oo7kp\".gW7J2CzXr,~/r\"W`<L8kal{!GxPrf.yK(J5B~lbvlS4\'\"4o53ha|qDM1_!d[CFrPCbNXu#Yg!HBA>Dizk<qdSsCX#!\'&1VyTqEV>`!CKR\'T8TsEZ;/SK\"RwCc|:S`F{30_k>tj[|a*0tv1]GoP[rh<ZFbeTJ8ielygbm!O`c7?ggdz5#?G[\"`y|_D^cW_Lf\'h}y=0VS|]:E>Lmu:_kZZo~xVKnjbU&2X%~teLn=Z6Y+;|-2JL~\\d/7?NsAl4`e7s?Q3=7B^^g!ArZDGko#kIr>biOpr&NA$\\rft0y+}A^6s|)%S<f<sO89v7pjsHJ@30u4/)DgUQ^Sv#O2r[_dGl+.b9Fh`(hFV#iiG1,B`B%>p{9k\"<\\O@}Y+^9b<#Edw+vKxuMfA:$QK)EerT\\8>0$B0j?S>ldpJK(-Ng!8IPMOnD?rNC|zIY2I9z%7M>)wXM2-8\"rx<Hr|ov<43(E?sOF6b2lrtr,%vtW(+|{nIFr<f$W5<@@%O>k2dSDh@j?3(da=26VTHJe\\=9T;.o0\'z).[Qu{B_Q{ODH$Y5@Gy%?nLD[ZgY5;k^Ti@\\vY|Sh$MD0&y_I*6GjM57\',b\\V8}N34vC,q7)TjxeqnK.V60y.!0%mYI`ifPMaLMXM@XloH]SC0jz(@/`TrD,B_Ks\'SIqv-#jF]NzB3:K.M|tEN!6h;3}^]C1a\'brURX[S~._XL\'PB%f.hVRt~|JNFK6Sn,mpdxv3,]wlOBr91,Am\"7gZ$nqiGX*[*d}ce!fLK)juNM[#)pbYTF\'Mp!oM+G17d`;uL1/JL{Sf?a+=\'-la.B7-/wlZL?\"}:qZC*%\'!ohw~8@/(],Jm1*!(:58*\"?&+f&{=OM21Kc?E4Ih{FS~bu~zhjJ&N}Cc;s~upoEqL0O}zp=z:&R^F.e#o/UM.-gMZ*h7.48Z}M:J;to<pQ[%acv&8xBJ7s`MW{.Z~m$g8.5!@+*c}39hEv)3eJ;eZ;3B.oC{%Z1d^-ye+tZ6t=NSe*bU?F5%qG`^9S}*-0JQ@sfG,DYWgLw$feaa5A[Np|*kSu9J@\'S~K,2\\\\R=-zr,8B29C7I96Wt?l<Bd7d,\"-Vi~Ot6zstuVe}v+:xU?b\\+}!1}^$U%PTRWx<CwJk?kspH<{Cjlm#u)35%64Pd*N,g+Xou(g7R#7g|UAR9u.bLMs$hM(x&K5dr?F*kh7riPB|5^K\\s,r(a[o<I7w5\"LG\"$Q`DatqYL2=_^z/!te;9Dn##?(k4lC76lM|irB|z\'b+u{)oMYd.M0c{1b./QEC/gLxHo6\"y^*m6{nTZx/[f<hA5P|A)A[,/K%Iy/wQD462BAjV,Ynj\"GpO#?EC>jxnr-jGR(E5^Z2d!}H{c\\$f$P-zao-.[.>y6]/}(9X~w4;^#Q<&dHVgd?R]2%gb\'&Zh?z.TSlyA})9bxIN,&\'^|MiOs\',JA)t%9QBLP.\'RhHoq*\\bYt,&a(dvk=#8{:/S<S`GJC25DWH58%5p7!!HIUBtm/7MTt\"l$#9K(~S}DC9;H6l$mxI|zs;>_78*@\\>qaC8p&T(yL\\tnK}_^_Q)lZO5N\')6-:f`KWSc?+&t83r(7MV\"#k2%J)fl\"5wQuvz)yqWUp/m2O7&&yqF|(b;kY54`ZMDo@n-J81~0fNX6zj8=d,;[pgz~bIkK67;6T}.*(XSsv3TcUlQoBY.KMzv9k]H.U(K~.@uke0H&w<,)R*#ouRGhR%Z^!\"-3VTbQ6A\"l6:5i2x~\\b)Y\"\\\";|9`H\"%&^O?WE7=(,:RRrPS\"uewtu<nQ_~2vgRaYG\'X{ilC!qGX~%h(piJb[L&PlFX`Xi9+}z*c(6H`f33Uw8X(,;|t2{azP?+Rymlw[P(tWhs\\cDW4)l<D8fY\'n5O%\"*\\H<I3Eu\"%+2?aTk8jEMZXD4|3Px]2*\\J[V/f\"0=n;U\\[gi+WD(*Ww`JLwtP=b)|7q-j{I40u:~?]im{Jkm}X!iw!}N&;)!66FVsAfk_cdJk{#)G.NtwsO>)otV^-nw>rlGqE-+f9h9=&RD.|%t49Bq\"O~mm!N{]\';IIG{Ik8|8[vug4Q+E<!EQFF\"{,\\O1{F.0z\"s5EU+(tpeZI{G<zW7m!HT?,MP8H*~rqC^l-u\",m`/xS7FwZzWO@wj^`+;}Eq7!`MWvfp&}#8^8<,N1Eh8*%JucdJk0a#b_Tyfi^7pTXG(n+0U!zXm]Kbo?2G~nkJ~\'].jS\"u4n(\\c(durq?b)o/]tR-+u\\/K,Gn<6J$s8%NJ[PQ.RNkMQI\'V*_(;|#N?$7X]t=(?~G(k=<6r6]&vYC7<XHRe^2q`vpQu6_gvS0L({mhkQ`2lzp{hgF/8Kx3Z&E$X8l;7Wb+Iaw*|hxLCY}o&)se8u~q\"*Uq;f.tXQ7h_!\"P}>:ZhEmC=V(n\"i?46xG[.\"%F3Db`Jc*l|Ii[-]rNZ~QB+2E#j;a4!!P`X7iBd<v^[VzJ.saRUQs{1!!;2w^E+J,6&>>>w2gj`59o<Yi3RN3Loc2\'WM8/+cOLnz*FpJVJsqd|U[CWiKKE0~Z&oQIf0`q1+~^5v[82j_~80=P;_d]X`H{|@QkhK&#b@_ll#1MD{H_:%e8V$g\"[1hX?4x}]y=r+aR$jH\'OA1-T|riL1wT{~pX52o9MD-m.$;|BEI{JaX8bUEZM0ds8Xokgv`RFh=E:_8YgX\'z@ak2=BKJ$dD_.=SswcUVQ_]dpZY2<:MsX}u}yxYUeO>Uu\"\"Tc%Kv{%[Gt<y<l=|}7\\KyI0:Fk`Y_S<[S,~TS)}6OzqfC@jV|SwR%3,%w7[\\|xH%k0rmoE\\aAA3{n9l\"UC@8Ypg>f4`~0.j\"oAS[!L0+5Er#1Sm~AiB)m0r!c/$Sw@47v~2s/%2S4d_i7vid4{6wgrp_z-XTN:-*CAm?|uUjh&K1TUQaY/H@e6_jO[lq)V16Zy:}Bd^o_)/pdKN;{3`K4yZmPb2UDZJ<<bz{Ueb:X&!w2=;AFvk^up\\[[f.a6>VUTA<!\\bte&#oX)8Nu(zLVGtNHPS8(of`8)v|ky,<x;:aA#Pzsk%g{y\\=D?TZ|$Ca~AqJ,}Pxo[rP4/RaWwx@=f).6TAC,-0$hV)OPZbIUk%o,^kgFMp\"K,S)mrhP&.E@@(NY<]0vYv<\\SCy4\\eM}9zc~mO\"CKyp\\,(~kPfMSEKq!>PCCyj}?jRvCXbtqcO-Z,!&flSk_{n>e}cCpL1p,fqg7a:\"uEwRt]zQL?.B34EV@4\\:_Jt?YL{RAU%1)Y_3m_\\Hk/E\\blW3-WWji}k&:8SRdgcox[7%{L.YA5N\"p0xezgIZT<|^XC2C>p$_Pl#ufQ6TcIn,*+L%hQ^\"Ak)H]\'kg`ZO$!15Lqtp0D:!I2G\"LiAX(3r%_<+#}g\"Yst+B#uAjf|oL8~A<:tqFj%zPR-%89;S<}=N{e|2wPTdiW0`x2:?M+09<qv|Puy@3Q*q.sW\\=@{XHxQ<t)\\}+zu0aDjTcUS9B?93Kh~-]nph~/z<J\"FGj59&^a0OW-vQgKdn\\}ci]0.%D7/H4cfD!\\_DF5^_xv;os6}(20q]gw}$N\'}:g>}aHX&MX/_E*e[de^sYW&2lt*k=6{f,Km8x#7qqq>uVgG2eedx<&SY)H{8,&e@L!2[0y/?}LXQ>->&S?0D3WTS)r)-covcIM)QMX\'Ha(a;AK5V,$/zMO*Tn4VHmfKcYSjo|Pb+R+7~l\"&e@w1=V0\'lr!f<VwFA=cW2L)6R9)6xa`/g9\\!=x{v]IjbBIm?)%gJA@PP_tui/R#XOt;S\"].M\':9M`/)puJlP@J74JcFDt(;uWrtK[)%93?IjOag{4{O@DJE$gV0_~IBK;da>TA?WpBr_E|a[s]|F}#uaF*F)a/MILt(~$<FNXr#Yr1?gea\\^-yK}K)rMC.ylZ8ulIuTIy&{2r\"]8(X9155$he}OE(HxDLC<TJG\\VLjz#j+kj0,s:$_\\]A+:BYemM|XzG0jBnUa\'z49amuUgx]I^dm/.(wO\"`ofe[nR{R)=(Zuc{lUm8uOFajd*Nn|!iN\"hA-WUwgS)e8dEDtsl#@^]\\\\/]dH5[U.a>cHl{9_+G#>n@Az!=VsjL\"#;KW};YP\\$Wtnzlb(w0v[FPJa9p6c4PcAm&>;6F|)}$a;=7op]>#Ut=\'@fa7.pj!R4a\"^s`U#@F-<5(:MJWsjyfLGHV\'Pn}ct^^xn9D=Wk\'f7{~cw3&U\"`LR.t&<MkkSEtBzCp!\'Sjy*D>vD.=[!*f*vZNXn-CAA)itz!M.u=~l2ZG7|[RAThPE+Q09H|%@??%<g,Up~11c<(T.`t0#)q-U2H*T[XaQ/:;+t:sWV1MDvc1^XGF\\dmmHdp!<IJpCDPB_!M77(1!JX}e,D((r\\[mAZ`.aLFjW!_)tG(H(?ID6}AW5V2vJ]V{Yy)gbGwxoMu_f>\\vY-K)*S`t{Ky;Q28]HvNGNsBqGL;B+[$?m|<4vl5_sLmm(>dH&KR*L0\"J*bexB\'zTn%>@ncDTU/`ful@TWhFiYk^3~Z*me*P)n{}+`\\Yw]^MbCxj_hZ_Tx522&OPY$LL2Vpt,pKnr134GHH7}!wKP&Ww~$BLY=a!=ZAs)=C1lm$aGP{:,)Zz<pS>>NR{ki1tK-!)nyA&X)?JMp|-`7P1K&yv7$$\\5g15G\\($2ze&aV\'9hsvC~s-[Cr3\\.EvH.wOVGTwKb9Pw\"%#bClO[UDg-zg%\'p.y!?h*qti7t`<V\"oaYapF@B7kIw&vc@(e}&K8Uj2)u\"g-\'Ea$;q4=\\\\UL@flTYd{1^2Rg;.Lq`%#^Yvtl~O`1-ZD3Nmj;Z5V0_\'.Fqh$U;JPIe0e^SKEm2&*?hHH?{h?KpwyZTB_f7_?n61\\wZ43\\Fj,.O1qt$l(uZg3)u5WqsX){1yI=?ay3zn6:nK}Me>}dRVpx3d&_ixePzf>5B1ug=a`&}TbUz>_2.&\';8{3WktAVKHaKI4:!;]3J$SXY[j=a!kI>ioD.K\'0^Tf@k1arJERSJ$f(K2`sMo3P7UbGU^J\"Yv4X4<>k3J`|;@=+7`.hsTYZ\\C8i=y0>qS!vx\"zyC%6k[S?r-M)Q!PG=EZ!\'1AMQM,$0CVgUkclA>Fp2j?$.mH78]|G$)4R/dMDxdzHAkSle~-Ya=ti{a\'=L^rL$i<`DX8*&`R4:u,-KN\"E\\rk@)`eMNRBq\\Q#sF+@r^2*{fz{O,S+O:>)E=l_~)I@i-,~]QUV8OO+9z9Z;6qi\"{Nbpvn\'V)bN}FW\\lXm={WJA3g*!iX6f~K\'gnLi-J+dL,CIDLN)2Z1?b],gd@Tw(TCWpFttt=I[)-Ahc(mnW[l*TyGo<u+o(<B3vQ.\\mG<_RPZC8G/*/bImt$a=j:xT1\\2gh|#SZMP>6!Ysj{y.mZ#e)lZ;;\":e,I6u=\\g.kEN&x?\":{@5,ej-Z~upSXv`4`8Wu%RxKFAO#8}j0x:$|VbtORzl-avak<Y==dab5-+>@_yZ?$4Vf3RFx7ny\"!0Gg,x\'0t~IsW~O#@^jQn!T=$Lvac$OtI8[rdYxM\'4}UcBZwj$P@\"HfZ9SL]c=1nOe.i=18x<+3Wdu2v8%9N;pOA~o{uc5%u&\\gm9o4Mi`A-Eq-MjS9#=#qo)CE4OzIZLnz?O{x!98WxdTE;rk5(d\'osQ%,RG^i@6Ny{QGLA~eJ=J,N}IBZd<`c_~C2&<k<\'`{eP^T[VO.vGQa]B(U<r]{qX2{!HZ}6>\"\'~E+<CHN6cf&hPom0Cj#vNtfll6^\"YaiD.RK(yd{BS@lWeLZ>kT4+&Nu((z~dc\'`R90At[?Ru&:TG(u)P,itH;1aJOP/6e7U-1bhkQymdnbw^R84ub:VjNQ+\"fa>Zt[|i}[f0lU&yTG{|M4w=+a&(d_iIdicbQ.CnW?bb\\-t^QrV/E%\'4+\"(=9Ue/\":5pi(M1>M\\=lV,Us@z1Y:?.c>K%_a.AOpK_z103ay7Fg\\}EF.nA\"%=cs)RbV+XbbOLrkj-pMk?/8e@]56ARIYNdb[&ae=yvs>P}{+~{#:yh*v2oY|LNHsaEL\\3B;l{MhGrd|Jx3QXtv%)f]Q!/X]<<E,>L2(;@Dq^cE#K[xMhwSG(`LRmy?F8RyK0.\'];fA]mDCD&)jN#CYujCIQbxV0jZ=tH[-5XP{6!\'v&*-x<?&ES22iiYr$&3`Qh1G3*\\u(-H.6Pa\'XCD1>\"8udmP\'bSvSe\'s?{eqf4&rJbgp6&]#KQB]6ULYwz|SH7bAoiT8*h(0~7;Rzu#V~l!!JC.ot08S8:F&Gq$t0HbG8F:lX&awkH38\'O8)_Q;WOz|ew\\H^fEr_@{}0Y<j*/{Yek(f/#QFoxr;_7fbj]\'8eblL(#TkW*2p$q\'D=qXp\\.9)Dvwax\\)>7`0j\\r%\')^/:^RB\"5[]w3o\\^?xmQzB7|$+qc>#d,Q5zfC;Gu\'S,\\%G#:VQM2u/>L[ekg:P_#I4:fyqp%>KZ-@wxm,e*9jcthv/QmOQwUl^[1\'?(p<Xdwh!E/`~B}&=Wn%9WFr0l8_.-$`vwET\"8O|\"S)w,pLK,_.aF{\\-7/|mq-)+E4L,Q$(-ZFu:=S_f73?&kZmPqH=x/7i-)?.9-T{h--eGbCsP`V-zf]1l!5yia{ppg16s5w/(z\'p1;P!z.Iy&(Z_|Z.HnU@3IH%];=hA\'a>vEL}uf{SlBnJ%jgvgF.;q=a+7u~&N<Z#ue64@\'VzMZ\"W^[~Q~GF8d^O,UPjQa]m]Qx#]&\\P8}@<?ypG4^)/e#oP0>9!i,uR[gc4Kv16D#dKxK+<7MDfbr9ZS#,Z*x|$E\'mPFR(\"\\k\\Q1Du!\"6AthX2t2TxLB1{:k\\n0a0NUz8_2?\\NryI$<JahKEYx&&dFVOq~cH}/\\>1:~Q\\CwWvf&g\"P>#ibWrSAs:66\\uV]_1?\\_.(ov\'{<S,_CGij}+NL\'[^0or\\DGU@\"+lAuV+8y&kmup1sN#^<AZ.b=?6T;w{EI,9dYB&b}I2P/E_=+,N9C]^_)?FD]F)BL+`-Am><pHQ7@fGim#cs)MJVs1NOsleMnW1|t04xs0#SE%}B[bUakA%8gTmkyxe*\\DLp1j!1C.OCB4.^9ky8[H,0B=Eg?m02unaCs2nE$@k!GLT<[M2;mA\'6@5|z00G21*<?3O9>*PEam\'bnjnSE@kasW60kBN5.3YF#&]\"e]%(YsnMo~V]sXR0g{II[8zS9rSJRt23;}(_Ttl2]7^LmlKNy\"\"[CDO-ez*F<m&19}C5sd[/W0Pd@B\"OpCA#lBO,SF)uv^3]FHYHt)N}ybrS_eQN96*hK9#21jo,fyGZ`FJGn~$/Sh+`1vJpqQ2siMDLO-}L2NDhjpdP]HbBG&(jGl7ui%,8D\'UD(PV{I)\\b,>PnfXIOtR\';VMaBQc>zPPQk\\}.cY!V7zf{&a8oP3ue43Dtki`iQo;>Iiuxi(nMCN\'N?sO8LBO}Zi>C#?;X4x0@[%E\'%K`-5Q\\!\'C[/jpOJWgD#3OVA\"E#qe_NsVWq@W_Td IuX$k\"!#+$//2w";

    str lambdaman22 = "B. SYU]}V^X~YWV}WV^~WV[}V]Z~W\\U}W^Y~WZ[}ZUX~WZY}ZW]~X] B. B$ L\" S Sum%4#m0!337$w SX}W\\\\~VWY}Y]~V^Y}V[Y~XW^}YUZ~V[Y}W\\~YWU}VV^~V]U}ZXY~XZW}WZY~X^W}VZ^~YZ\\}^Z~W]\\}ZX]~VY]}\\^~V\\]}VUY~W\\[}XUY~XWV}Y^]~YVX}VXW~V[]}VX\\~WXX}Z[]~W]X}YXW~WXX}VY^~X\\\\}WZY~V][}V][~WZ[}ZY[~WUZ}ZXV~X[[}W\\Y~W\\W}X\\]~W^Y}XXU~Y\\]}]Z~YV[}VYU~V]U}]\\~X[X}X]Z~V]V}ZZU~W\\Y}ZYU~Y]X}X\\~XZ^}XZW~V][}Z]X~WU\\}VUY~X^]}WZ[~W\\\\}YZY~WWZ}V\\Z~V\\\\}^X~Y[W}VU\\~WUV}VW[~XUX}YZ[~XZ^}XYV~W\\^}Z[Y~W]X}YX[~XVX}YW]~X\\Z}V^]~Y[X}\\]~YZZ}VYV~X\\X}XZ]~WY^}ZXV~WYX}W[V~YYU}VU\\~WX[}ZX]~X\\Z}W[V~XYY}X[X~XVZ}ZU[~WXY}WVU~XUV}ZXW~VX]}\\X~WUW}VX\\~Y[W}YX~X\\V}XVU~XVV}X][~X\\U}W\\W~XUX}YYZ~Y[V}[U~W^X}Y][~XY\\}XW\\~VZ]}VWU~YWY}VYU~W\\V}X[]~YXV}VV^~YZY}ZV~W[Z}ZYV~V[Z}VU\\~VXW}ZZ~W^V}Y[\\~WVX}WWZ~YU^}WYZ~V^V}ZV~W^^}XUX~Y[[}VWU~XVX}XVW~XW^}XXZ~V[U}\\X~X[V}XXU~WWY}V]U~W^[}Y\\\\~X\\Z}WV\\~WYX}Z\\^~XY]}W^Y~WXW}ZZZ~WZ[}Z\\V~XUU}ZWY~Y\\^}[U~VX^}[Z~W[[}WZU~YV\\}V^V~XWU}XZW~X]\\}WWY~X\\U}W^\\~XU[}YV]~XWY}X]Y~VZ]}^Y~WY\\}ZZ^~XUV}X\\Y~V\\]}ZY~YX\\}YZ~WVX}V[\\~VX[}ZZ~X^U}VY]~XV^}YWV~VWU}XW~YUW}VYV~WUY}]Z~W^X}XU^~XUU}Y^U~WWY}WUZ~YU[}VXW~VY[}^Z~XU[}XZV~WUY}VZZ~WX^}WYY~W^[}ZX]~XVV}Y^V~VV]}W^~X\\U}X\\V~W^V}XZ^~YXV}V[X~WZV}V]V~X\\V}W^Y~WY^}XVZ~XX^}XZY~W^X}YXW~XY]}WZW~Y\\V}YU~W[]}ZYZ~X]X}XW\\~YUU}W^U~XUU}X\\\\~XUW}ZWZ~WZX}WX]~XWU}YZX~XZ\\}W[[~WUZ}WVX~WZV}XW\\~YUV}WX[~YWX}VV^~W[W}ZZZ~Y\\X}ZW~XUX}Y[[~XWY}YU]~WVZ}WY\\~X[[}X[[~V]\\}VUU~YXX}VUW~WXZ}V\\X~V\\\\}X[~W\\Z}ZY]~X[V}X[Z~X^[}VXV~VYU}[]~W\\^}WZ[~XZV}YU]~XYV}XY[~X^Z}XUV~WX\\}WZX~X\\U}W^U~YUU}V]\\~YVZ}V]V~XW[}XZV~YVY}VUU~YU]}VWU~W[\\}WVV~WV\\}V^\\~YU]}VWY~WW^}VYX~VZY}^W~X[V}X[]~YVX}V][~WWZ}Z]U~W[Y}WYZ~XZX}X^Y~W]X}XYW~XZZ}W\\Z~YV[}WZZ~WZZ}XXW~XY^}W]^~V^V}ZXY~W^[}Y[]~V]^}VW]~V]U}V[W~V]^}V[\\~Y]U}X]~W]W}ZW^~Y[]}Z^~XV\\}YXV~X]]}WZ]~XW^}YWZ~WUV}Z[^~W^U}ZZ\\~Y\\\\}[Y~XY[}W]]~XUV}ZWY~W[X}ZWX~WWW}WVZ~YX]}[Y~W^[}YWW~WXZ}V[X~V^U}ZYZ~V]Z}Z\\Z~W[\\}WYW~W\\\\}W\\Y~X[]}XX^~XYX}YVV~V]V}VYZ~XZ\\}XV^~W\\W}W^Y~X]^}W]V~WXY}WV]~WZ\\}V^W~XYW}W^X~X]W}WW[~X]V}WX^~XZX}WYX~W\\\\}XV[~X^^}W[V~XV\\}Y]Z~XYU}YX]~W[Z}WYX~W]Y}YX[~X^V}WYY~V[Z}]X~W[U}Z[Y~YZU}V[Y~WZ[}ZW\\~YUV}WYY~V]\\}Z\\Z~WX[}ZYY~V][}V][~Y[[}VV]~Y[W}[V~W[]}W\\V~WXY}VYU~WV\\}WU]~W\\Y}W]W~X^Z}V[U~WW[}VZ^~WVV}VYV~X\\]}V\\W~WZX}XUU~WWZ}Z]W~WVX}VU[~X^^}VYY~W\\X}Y^]~WY^}WU]~W[^}W\\^~W]Z}X[W~WY]}Z\\X~XU]}XY^~W[U}ZW^~XZ\\}W[Y~XWZ}Y[W~V]W}VW\\~Y[\\}\\^~WUY}WU]~WWV}V^Y~VZY}^Z~V]W}X]~XYW}XXY~YXV}WVZ~XY[}XZ\\~X[W}X]W~XXX}Y[V~V^U}VXZ~WZ\\}Z[X~W^Y}X\\Y~XUY}Y^[~W\\W}XV\\~YX\\}\\X~VYV}W[~XYY}YX[~VY]}\\Z~WZ\\}ZVX~V]V}^V~YV\\}WWV~YVY}WY]~WYZ}V]U~W[V}WW^~V]W}VVV~WU]}VYW~";

  auto fn = [] (str code) {
    vec<str> ts = tokenize(code);
    // cerr << ts << endl;
    each (t, ts) q.push(t);
    eval();
    assert(q.empty());
  };
  fn(lambdaman22);

  return 0;
}
