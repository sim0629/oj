#include <algorithm>
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

int n_friends, n_foods;
unordered_map<string, int> friend_name_to_idx;
vector<long long> food_masks;
long long all_done;

int recursive(int idx, long long mask) {
  if (mask == all_done) {
    return 0;
  }
  if (idx == n_foods) {
    return n_foods;
  }

  // must not choose current idx
  long long next_mask = mask | food_masks[idx];
  if (mask == next_mask) {
    return recursive(idx + 1, mask);
  }

  // must choose current idx
  long long future_mask = mask;
  for (int i = idx + 1; i < n_foods; i++) {
    future_mask |= food_masks[i];
  }
  if ((future_mask | food_masks[idx]) != future_mask) {
    return 1 + recursive(idx + 1, mask | food_masks[idx]);
  }

  // don't know choose or not
  int case_a = 1 + recursive(idx + 1, mask | food_masks[idx]);
  int case_b = recursive(idx + 1, mask);
  return min(case_a, case_b);
}

int solve() {
  all_done = (1ll << n_friends) - 1;
  return recursive(0, 0ll);
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    cin >> n_friends >> n_foods;
    friend_name_to_idx.clear();
    for (int i = 0; i < n_friends; i++) {
      string name;
      cin >> name;
      friend_name_to_idx[name] = i;
    }
    food_masks.clear();
    for (int i = 0; i < n_foods; i++) {
      long long food_mask = 0;
      int n;
      cin >> n;
      for (int j = 0; j < n; j++) {
        string name;
        cin >> name;
        int idx = friend_name_to_idx[name];
        food_mask |= (1ll << idx);
      }
      food_masks.push_back(food_mask);
    }
    cout << solve() << '\n';
  }
  return 0;
}
