#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

void solve(int n, int k) {
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    q.push(i);
  }
  for (int i = 0; i < n - 2; i++) {
    q.pop();
    for (int j = 0; j < k - 1; j++) {
      int v = q.front();
      q.pop();
      q.push(v);
    }
  }
  if (q.front() < q.back()) {
    cout << q.front() << ' ' << q.back() << '\n';
  } else {
    cout << q.back() << ' ' << q.front() << '\n';
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    int n, k;
    cin >> n >> k;
    solve(n, k);
  }
  return 0;
}
