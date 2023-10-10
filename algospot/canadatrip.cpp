#include <algorithm>
#include <cmath>
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

int N, K;
int L[5000], M[5000], G[5000];

int signages_until(int p) {
  int cnt = 0;
  for (int i = 0; i < N; i++) {
    int l = L[i], m = M[i], g = G[i];
    if (p < l - m) {
      cnt += 0;
    } else if (p >= l) {
      cnt += (m / g + 1);
    } else {
      cnt += (p - (l - m)) / g + 1;
    }
  }
  return cnt;
}

int find_kth() {
  int left = 0; // not ok
  int right = 8030000; // ok
  while (left + 1 < right) {
    int mid = (left + right) / 2;
    if (signages_until(mid) >= K) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return right;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
      cin >> L[i] >> M[i] >> G[i];
    }
    int pos = find_kth();
    cout << pos << '\n';
  }
  return 0;
}
