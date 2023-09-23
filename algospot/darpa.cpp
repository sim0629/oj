#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<int> pos;

int bin(int l, int r) {
  if (l + 1 >= r) {
    return l;
  }
  int dist = (l + r) / 2;

  int last_pos = pos[0];
  int pick_cnt = 1;
  for (int i = 1; i < pos.size(); i++) {
    if (pos[i] - last_pos >= dist) {
      last_pos = pos[i];
      pick_cnt++;
    }
  }
  if (pick_cnt >= N) {
    return bin(dist, r);
  } else {
    return bin(l, dist);
  }
}

int solve() {
  return bin(0, 24001);
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C, M;
  cin >> C;
  while (C--) {
    cin >> N >> M;
    pos.clear();
    for (int i = 0; i < M; i++) {
      float f;
      cin >> f;
      int p = round(f * 100);
      pos.push_back(p);
    }
    int ans = solve();
    cout << fixed;
    cout.precision(2);
    cout << ((float)ans / 100) << '\n';
  }
  return 0;
}
