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
vector<pair<double, double>> stations;

bool possible(double range) {
  bool visited[100] = {};
  queue<int> q;
  q.push(0);
  visited[0] = true;
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    double x, y;
    tie(x, y) = stations[cur];
    for (int next = 0; next < N; next++) {
      if (visited[next] || next == cur) {
        continue;
      }
      double x2, y2;
      tie(x2, y2) = stations[next];
      if ((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y) < range * range) {
        q.push(next);
        visited[next] = true;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    if (!visited[i]) {
      return false;
    }
  }
  return true;
}

double solve() {
  double left = 0;
  double right = 2000;
  while (right - left > 1e-4) {
    double mid = (left + right) / 2;
    if (possible(mid)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return right;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  cout << fixed;
  cout.precision(2);
  int C;
  cin >> C;
  while (C--) {
    cin >> N;
    stations.clear();
    for (int i = 0; i < N; i++) {
      double x, y;
      cin >> x >> y;
      stations.emplace_back(x, y);
    }
    double answer = solve();
    cout << answer << '\n';
  }
  return 0;
}
