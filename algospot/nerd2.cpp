#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int N;
int p[50000];
int q[50000];

void print_set(const set<pair<int, int>>& s) {
  for (auto pq : s) {
    cout << '(' << pq.first << ',' << pq.second << ')' << ' ';
  }
  cout << '\n';
}

int solve() {
  int total = 0;
  set<pair<int, int>> pareto;
  for (int i = 0; i < N; i++) {
    auto pq = make_pair(p[i], q[i]);
    auto it_bigger = lower_bound(pareto.begin(), pareto.end(), pq);
    if (it_bigger != pareto.end()) {
      if ((*it_bigger).second > q[i]) {
        total += pareto.size();
        continue;
      }
    }
    auto it = pareto.insert(pq).first;
    if (it != pareto.begin()) {
      auto next_it = prev(it);
      while (true) {
        it = next_it;
        if ((*it).second > q[i]) {
          break;
        }
        if (it == pareto.begin()) {
          pareto.erase(it);
          break;
        } else {
          next_it = prev(it);
          pareto.erase(it);
        }
      }
    }
    total += pareto.size();
  }
  return total;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> p[i] >> q[i];
    }
    cout << solve() << '\n';
  }
  return 0;
}
