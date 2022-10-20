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

int n;
int triangle[100][100];
int max_sum[100][100];
int ways[100][100];

int solve() {
  max_sum[0][0] = triangle[0][0];
  ways[0][0] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == i || max_sum[i - 1][j - 1] > max_sum[i - 1][j]) {
        max_sum[i][j] = max_sum[i - 1][j - 1] + triangle[i][j];
        ways[i][j] = ways[i - 1][j - 1];
      } else if (j == 0 || max_sum[i - 1][j - 1] < max_sum[i - 1][j]) {
        max_sum[i][j] = max_sum[i - 1][j] + triangle[i][j];
        ways[i][j] = ways[i - 1][j];
      } else {
        max_sum[i][j] = max_sum[i - 1][j] + triangle[i][j];
        ways[i][j] = ways[i - 1][j - 1] + ways[i - 1][j];
      }
    }
  }
  int max_max_sum = 0;
  for (int j = 0; j <= n - 1; j++) {
    max_max_sum = max(max_max_sum, max_sum[n - 1][j]);
  }
  int total_ways = 0;
  for (int j = 0; j <= n - 1; j++) {
    if (max_sum[n - 1][j] == max_max_sum) {
      total_ways += ways[n - 1][j];
    }
  }
  return total_ways;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
        cin >> triangle[i][j];
      }
    }
    cout << solve() << '\n';
  }
  return 0;
}
