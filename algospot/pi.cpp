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

const int INF = 100000;
string s;
int n;
int memo[10001];

bool isDiff1(int from, int to) {
  char c = s[from];
  for (int i = from + 1; i <= to; i++) {
    if (c != s[i]) {
      return false;
    }
  }
  return true;
}

bool isDiff2(int from, int to) {
  char c0 = s[from];
  char c1 = s[from + 1];
  if (c1 == c0 + 1) {
    for (int i = from + 2; i <= to; i++) {
      if (s[i] != s[i - 1] + 1) {
        return false;
      }
    }
  } else if (c1 == c0 - 1) {
    for (int i = from + 2; i <= to; i++) {
      if (s[i] != s[i - 1] - 1) {
        return false;
      }
    }
  } else {
    return false;
  }
  return true;
}

bool isDiff4(int from, int to) {
  char c0 = s[from];
  char c1 = s[from + 1];
  for (int i = from + 2; i <= to; i++) {
    if ((i - from) % 2 == 0) {
      if (s[i] != c0) {
        return false;
      }
    } else {
      if (s[i] != c1) {
        return false;
      }
    }
  }
  return true;
}

bool isDiff5(int from, int to) {
  char c0 = s[from];
  char c1 = s[from + 1];
  for (int i = from + 2; i <= to; i++) {
    if (s[i] - s[i - 1] != c1 - c0) {
      return false;
    }
  }
  return true;
}

int diff(int from) {
  if (from == n) {
    return 0;
  }
  if (memo[from] != 0) {
    return memo[from];
  }
  int& ret = memo[from];
  int minDiff = INF;
  for (int digits = 3; digits <= 5; digits++) {
    if (n - from < digits) {
      continue;
    }
    if (isDiff1(from, from + digits - 1)) {
      minDiff = min(minDiff, diff(from + digits) + 1);
    } else if (isDiff2(from, from + digits - 1)) {
      minDiff = min(minDiff, diff(from + digits) + 2);
    } else if (isDiff4(from, from + digits - 1)) {
      minDiff = min(minDiff, diff(from + digits) + 4);
    } else if (isDiff5(from, from + digits - 1)) {
      minDiff = min(minDiff, diff(from + digits) + 5);
    } else {
      minDiff = min(minDiff, diff(from + digits) + 10);
    }
  }
  return ret = minDiff;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> s;
    n = s.length();
    fill(memo, memo + n, 0);
    cout << diff(0) << '\n';
  }
  return 0;
}
