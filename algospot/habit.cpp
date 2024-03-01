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

int K;
string S;
int N;

struct Comparator {
  const vector<int> &g;
  int t;
  Comparator(const vector<int> &_g, int _t) : g(_g), t(_t) {}
  bool operator() (int a, int b) {
    if (g[a] != g[b]) return g[a] < g[b];
    else return g[a + t] < g[b + t];
  }
};

vector<int> build_suffix_array() {
  vector<int> group(N + 1);
  group[N] = -1;
  for (int i = 0; i < N; i++) {
    group[i] = S[i];
  }
  vector<int> suffix(N);
  for (int i = 0; i < N; i++) {
    suffix[i] = i;
  }
  int t = 1;
  while (t < N) {
    Comparator comp(group, t);
    sort(suffix.begin(), suffix.end(), comp);
    t *= 2;
    if (t >= N) break;
    vector<int> new_group(N + 1);
    new_group[N] = -1;
    new_group[suffix[0]] = 0;
    for (int i = 1; i < N; i++) {
      if (comp(suffix[i - 1], suffix[i])) {
        new_group[suffix[i]] = new_group[suffix[i - 1]] + 1;
      } else {
        new_group[suffix[i]] = new_group[suffix[i - 1]];
      }
    }
    group = new_group;
  }
  return suffix;
}

int longest_common_prefix(int a, int b) {
  int l = 0;
  while (a < N && b < N && S[a] == S[b]) {
    a++;
    b++;
    l++;
  }
  return l;
}

int solve() {
  vector<int> suffix = build_suffix_array();
  int max_len = 0;
  for (int i = 0; i + K - 1 < N; i++) {
    max_len = max(max_len, longest_common_prefix(suffix[i], suffix[i + K - 1]));
  }
  return max_len;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> K >> S;
    N = S.size();
    cout << solve() << '\n';
  }
  return 0;
}
