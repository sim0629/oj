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

int n;
int numbers[50];
unordered_map<int, int> memo;
const int INF = 100000;

int key(int left, int right) {
  return left * 100 + right;
}

int game(int left, int right) {
  int k = key(left, right);
  if (memo.find(k) != memo.end()) {
    return memo[k];
  }
  if (left > right) {
    return memo[k] = 0;
  }
  int best = -INF;
  best = max(best, numbers[left] - game(left + 1, right));
  best = max(best, numbers[right] - game(left, right - 1));
  if (left + 1 <= right) {
    best = max(best, -game(left + 2, right));
    best = max(best, -game(left, right - 2));
  }
  return memo[k] = best;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> numbers[i];
    }
    memo.clear();
    cout << game(0, n - 1) << '\n';
  }
  return 0;
}
