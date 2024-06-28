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

const str table = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&\'()*+,-./:;<=>?@[\\]^_`|~ \n";
map<char, int> inv;

str translate(str s)
{
  str t;
  each (c, s) t += table.at(c - 33);
  cerr << s << "->" << t << endl;
  return t;
}

str base94(str s)
{
  lli x = 0;
  each (c, s) x = x * 94 + (c - 33);
  return to_string(x);
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
  if (q.size()) cerr << indicator << ' ' << q.front() << endl;
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
      cout << "(not "; eval(); cout << ")";
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
  cout << "(define-obsolete-function-alias \'string-to-int \'string-to-number \"22.1\")" << endl;
  cout << "(add-to-list \'load-path \"./site-lisp/bigint/\")" << endl;
  cout << "(add-to-list \'load-path \"./site-lisp/s\")" << endl;
  cout << "(require \'s)" << endl;
  cout << "(require \'bigint)" << endl;
  cout << "(defun T () t)" << endl;
  cout << "(defun F () nil)" << endl;
  cout << "(defmacro take (len s) (s-left  len s))" << endl;
  cout << "(defmacro drop (len s) (s-right len s))" << endl;

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

  auto fn = [] (str code) {
    vec<str> ts = tokenize(code);
    cerr << ts << endl;
    each (t, ts) q.push(t);
    eval();
    assert(q.empty());
  };
  fn(lambdaman10);

  return 0;
}
