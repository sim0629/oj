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
int x[100], y[100], r[100];

int parents[100];
int depths[100];

void construct_tree() {
  for (int i = 1; i < N; i++) {
    int min_r = 2000;
    int min_r_j = -1;
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      // i is in j?
      if (r[i] < r[j] && (x[j] - x[i]) * (x[j] - x[i]) + (y[j] - y[i]) * (y[j] - y[i]) < r[j] * r[j]) {
        if (r[j] < min_r) {
          min_r = r[j];
          min_r_j = j;
        }
      }
    }
    parents[i] = min_r_j;
  }
}

void calc_depths() {
  for (int i = 1; i < N; i++) {
    int d = 1;
    int cur = parents[i];
    while (cur > 0) {
      d++;
      cur = parents[cur];
    }
    depths[i] = d;
  }
}

int calc_distance(int i, int j) {
  int dist = 0;
  int di = depths[i];
  int dj = depths[j];
  int ci = i, cj = j;
  while (di > dj) {
    ci = parents[ci];
    di--;
    dist++;
  }
  while (dj > di) {
    cj = parents[cj];
    dj--;
    dist++;
  }
  while (ci != cj) {
    ci = parents[ci];
    cj = parents[cj];
    dist += 2;
  }
  return dist;
}

int calc_max_distance() {
  if (N == 1) {
    return 0;
  }
  int m = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      m = max(m, calc_distance(i, j));
    }
  }
  return m;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> x[i] >> y[i] >> r[i];
      parents[i] = 0;
    }
    construct_tree();
    calc_depths();
    cout << calc_max_distance() << '\n';
  }
  return 0;
}
