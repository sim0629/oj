#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

void solve(int N, vector<tuple<int, int>>& heightAndIndexes) {
  int maxArea = 0;

  sort(heightAndIndexes.begin(), heightAndIndexes.end());

  set<int> indexesSoFar;
  indexesSoFar.insert(-1);
  indexesSoFar.insert(N);

  for (auto& heightAndIndex : heightAndIndexes) {
    int height, index;
    tie(height, index) = heightAndIndex;
    auto right = indexesSoFar.lower_bound(index);
    auto left = prev(right);
    int width = *right - *left - 1;
    maxArea = max(maxArea, width * height);
    indexesSoFar.insert(index);
  }

  cout << maxArea << '\n';
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    int N;
    cin >> N;
    vector<tuple<int, int>> heightAndIndexes;
    for (int i = 0; i < N; i++) {
      int h;
      cin >> h;
      heightAndIndexes.emplace_back(h, i);
    }
    solve(N, heightAndIndexes);
  }
  return 0;
}
