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

using namespace std;

const int INF = 1000000000;
int N;
int S;
int A[100];
int Asum[100];
int memo[100][100][11];

int dp(int x, int y, int s) {
  if (x == y) {
    return 0;
  }
  int& ret = memo[x][y][s];
  if (ret != -1) {
    return ret;
  }
  if (s == 1) {
    int sum = x > 0 ? Asum[y] - Asum[x - 1] : Asum[y];
    int num = y - x + 1;
    // the nearest integer of (sum / num)
    int avg = sum / num + ((sum % num) > (num / 2) ? 1 : 0);
    int total = 0;
    for (int a = x; a <= y; a++) {
      total += (A[a] - avg) * (A[a] - avg);
    }
    return ret = total;
  }
  int minSquareSum = INF;
  for (int mid = x; mid < y; mid++) {
    // [x, mid] | [mid + 1, y]
    for (int z = 1; z < s; z++) {
      minSquareSum = min(minSquareSum, dp(x, mid, z) + dp(mid + 1, y, s - z));
    }
  }
  return ret = minSquareSum;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N >> S;
    for (int i = 0; i < N; i++) {
      cin >> A[i];
    }
    sort(A, A + N);
    Asum[0] = A[0];
    for (int i = 1; i < N; i++) {
      Asum[i] = Asum[i - 1] + A[i];
    }
    memset(&memo[0][0][0], -1, sizeof(memo));
    cout << dp(0, N - 1, S) << '\n';
  }
  return 0;
}
