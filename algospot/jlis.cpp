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

int n, m;
int A[100], B[100];
unordered_map<int, int> memo;

int jlis(int a, int b) {
  int memoKey = (a + 1) * 1000 + (b + 1);
  if (memo.find(memoKey) != memo.end()) {
    return memo[memoKey];
  }
  if (a == -1 && b == -1) {
    return 0;
  }
  int max_length = 1;
  if (b == -1 || a >= 0 && A[a] > B[b]) {
    // A[a]가 맨 마지막 원소
    for (int ai = a - 1; ai >= -1; ai--) {
      if (ai == - 1 || A[ai] < A[a]) {
        max_length = max(max_length, jlis(ai, b) + 1);
      }
    }
  }
  if (a == -1 || b >= 0 && B[b] > A[a]) {
    // B[b]가 맨 마지막 원소
    for (int bi = b - 1; bi >= -1; bi--) {
      if (bi == -1 || B[bi] < B[b]) {
        max_length = max(max_length, jlis(a, bi) + 1);
      }
    }
  }
  if (A[a] == B[b]) {
    for (int ai = a - 1; ai >= -1; ai--) {
      if (ai >= 0 && A[ai] >= A[a]) {
        continue;
      }
      for (int bi = b - 1; bi >= -1; bi--) {
        if (bi >= 0 && B[bi] >= B[b]) {
          continue;
        }
        max_length = max(max_length, jlis(ai, bi) + 1);
      }
    }
  }
  return memo[memoKey] = max_length;
}

int solve() {
  memo.clear();
  int max_length = 0;
  for (int a = 0; a < n; a++) {
    for (int b = 0; b < m; b++) {
      max_length = max(max_length, jlis(a, b));
    }
  }
  return max_length;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int c;
  cin >> c;
  while (c--) {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }
    for (int i = 0; i < m; i++) {
      cin >> B[i];
    }
    cout << solve() << '\n';
  }
  return 0;
}
