#include <algorithm>
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

int N;
map<int, int> pareto;

void insertToPareto(int p, int q) {
  auto it_bigger = pareto.lower_bound(p);
  if (it_bigger != pareto.end()) {
    if ((*it_bigger).second > q) {
      return;
    }
  }
  auto it = pareto.insert(make_pair(p, q)).first;
  if (it != pareto.begin()) {
    auto next_it = prev(it);
    while (true) {
      it = next_it;
      if ((*it).second > q) {
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
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    int p, q;
    cin >> N;
    pareto.clear();
    int total = 0;
    for (int i = 0; i < N; i++) {
      cin >> p >> q;
      insertToPareto(p, q);
      total += pareto.size();
    }
    cout << total << '\n';
  }
  return 0;
}
