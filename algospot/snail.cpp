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

unordered_map<int, double> memoizedProb;

double prob(int meters, int days) {
  if (days == 0) {
    return meters == 0 ? 1.0 : 0.0;
  }
  int key = meters * 10000 + days;
  if (memoizedProb.find(key) != memoizedProb.end()) {
    return memoizedProb[key];
  }
  double p = (prob(meters - 1, days - 1) + prob(meters - 2, days - 1) * 3.0) / 4.0;
  return memoizedProb[key] = p;
}

double solve(int n, int m) {
  double p = 0;
  int days = m;
  for (int meters = m; meters <= 2 * m; meters++) {
    if (meters >= n) {
      p += prob(meters, days);
    }
  }
  return p;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    int n, m;
    cin >> n >> m;
    cout.precision(10);
    cout << solve(n, m) << '\n';
  }
  return 0;
}
