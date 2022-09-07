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

int N;
int ground[100][100];
unordered_map<tuple<int, int>, bool, HashTuple> reachable;

bool isReachable(int x, int y) {
  auto key = make_tuple(x, y);
  if (reachable.find(key) != reachable.end()) {
    return reachable[key];
  }
  for (int i = 1; i <= 9; i++) {
    if (x - i >= 0 && ground[x - i][y] == i) {
      if (isReachable(x - i, y)) {
        return reachable[key] = true;
      }
    }
  }
  for (int j = 1; j <= 9; j++) {
    if (y - j >= 0 && ground[x][y - j] == j) {
      if (isReachable(x, y - j)) {
        return reachable[key] = true;
      }
    }
  }
  return reachable[key] = false;
}

void solve() {
  reachable.clear();
  reachable[make_tuple(0, 0)] = true;
  if (isReachable(N - 1, N - 1)) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> ground[i][j];
      }
    }
    solve();
  }
  return 0;
}
