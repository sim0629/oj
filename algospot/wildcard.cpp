#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct HashTuple {
  template <class T1, class T2>
  size_t operator() (const tuple<T1, T2>& x) const {
    return get<0>(x) ^ get<1>(x);
  }
};

string W;
int N;
string Q;
unordered_map<tuple<int, int>, bool, HashTuple> memo;

bool matches(int wi, int qi) {
  if (wi == -1) {
    return qi == -1;
  }
  auto key = make_tuple(wi, qi);
  if (memo.find(key) != memo.end()) {
    return memo[key];
  }
  if (W[wi] == '*') {
    if (qi == -1) {
      return memo[key] = matches(wi - 1, qi);
    }
    if (matches(wi, qi - 1)) {
      return memo[key] = true;
    }
    if (matches(wi - 1, qi)) {
      return memo[key] = true;
    }
    if (matches(wi - 1, qi - 1)) {
      return memo[key] = true;
    }
  } else if (W[wi] == '?') {
    if (qi >= 0 && matches(wi - 1, qi - 1)) {
      return memo[key] = true;
    }
  } else {
    if (qi >= 0 && W[wi] == Q[qi] && matches(wi - 1, qi - 1)) {
      return memo[key] = true;
    }
  }
  return memo[key] = false;
}

bool matches() {
  memo.clear();
  return matches(W.length() - 1, Q.length() - 1);
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> W;
    set<string> matched;
    cin >> N;
    while (N--) {
      cin >> Q;
      if (matches()) {
        matched.insert(Q);
      }
    }
    for (auto& m : matched) {
      cout << m << '\n';
    }
  }
  return 0;
}
