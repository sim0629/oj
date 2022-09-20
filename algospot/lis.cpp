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
int seq[500];
int dp[500];

int lis() {
  int longest = 0;
  for (int i = 0; i < N; i++) {
    int max_length = 0;
    for (int j = 0; j < i; j++) {
      if (seq[j] < seq[i]) {
        max_length = max(max_length, dp[j]);
      }
    }
    dp[i] = max_length + 1;
    longest = max(longest, dp[i]);
  }
  return longest;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> seq[i];
    }
    cout << lis() << '\n';
  }
  return 0;
}
