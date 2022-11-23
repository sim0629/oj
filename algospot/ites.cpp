#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int solve(int k, int n) {
  unsigned int a = 1983;

  queue<int> q;
  int total = 0;
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    int signal = a % 10000 + 1;

    q.push(signal);
    total += signal;

    while (total >= k) {
      if (total == k) {
        cnt++;
      }
      int v = q.front();
      q.pop();
      total -= v;
    }

    a = a * 214013 + 2531011;
  }

  return cnt;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    int K, N;
    cin >> K >> N;
    cout << solve(K, N) << '\n';
  }
  return 0;
}
