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

int N;
int triangle[100][100];
int dp[100][100];

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j <= i; j++) {
        cin >> triangle[i][j];
      }
    }
    dp[0][0] = triangle[0][0];
    for (int i = 1; i < N; i++) {
      for (int j = 0; j <= i; j++) {
        int dp_1;
        if (j == 0) {
          dp_1 = dp[i - 1][j];
        } else if (j == i) {
          dp_1 = dp[i - 1][j - 1];
        } else {
          dp_1 = max(dp[i - 1][j - 1], dp[i - 1][j]);
        }
        dp[i][j] = triangle[i][j] + dp_1;
      }
    }
    int max_sum = dp[N - 1][0];
    for (int j = 1; j < N; j++) {
      max_sum = max(max_sum, dp[N - 1][j]);
    }
    cout << max_sum << '\n';
  }
  return 0;
}
