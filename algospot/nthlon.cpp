#include <algorithm>
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

const int INF = 987654321;
int M;
int A[500], B[500];

int solve() {
  priority_queue<pair<int, int>> q;
  unordered_map<int, int> d;
  q.emplace(0, 0);
  while (!q.empty()) {
    int sofar, here;
    tie(sofar, here) = q.top();
    q.pop();
    sofar = -sofar;
    if (sofar != 0 && here == 0) {
      return sofar;
    }
    if (d.find(here) != d.end() && sofar > d[here]) {
      continue;
    }
    for (int m = 0; m < M; m++) {
      int there = here + A[m] - B[m];
      int tofar = sofar + A[m];
      if (there < 200 && there > -200) {
        if (d.find(there) == d.end() || tofar < d[there]) {
          d[there] = tofar;
          q.emplace(-tofar, there);
        }
      }
    }
  }
  return INF;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> M;
    for (int i = 0; i < M; i++) {
      cin >> A[i] >> B[i];
    }
    int dist = solve();
    if (dist == INF) {
      cout << "IMPOSSIBLE";
    } else {
      cout << dist;
    }
    cout << '\n';
  }
  return 0;
}
