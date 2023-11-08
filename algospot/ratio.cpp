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

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    long long N, M;
    cin >> N >> M;

    long long Z = M * 100 / N;
    if (Z >= 99) {
      cout << -1 << '\n';
      continue;
    }
    long long W = Z + 1;
    long long bj = W * N - 100 * M;
    long long bm = 100 - W;
    if (bj % bm == 0) {
      cout << bj / bm << '\n';
    } else {
      cout << bj / bm + 1 << '\n';
    }
  }
  return 0;
}
