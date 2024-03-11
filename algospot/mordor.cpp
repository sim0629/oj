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

const int MAX_H = 20000;
const int MIN_H = 0;

int N, Q;
int h[100000];
int min_tree[500000];
int max_tree[500000];

int build_min_tree(int left, int right, int node) {
  if (left >= right) {
    return min_tree[node] = h[left];
  }
  int mid = (left + right) / 2;
  int left_min = build_min_tree(left, mid, node * 2);
  int right_min = build_min_tree(mid + 1, right, node * 2 + 1);
  return min_tree[node] = min(left_min, right_min);
}

int build_max_tree(int left, int right, int node) {
  if (left >= right) {
    return max_tree[node] = h[left];
  }
  int mid = (left + right) / 2;
  int left_max = build_max_tree(left, mid, node * 2);
  int right_max = build_max_tree(mid + 1, right, node * 2 + 1);
  return max_tree[node] = max(left_max, right_max);
}

void build() {
  build_min_tree(0, N - 1, 1);
  build_max_tree(0, N - 1, 1);
}

int query_min(int a, int b, int left, int right, int node) {
  if (a <= left && right <= b) {
    return min_tree[node];
  }
  if (right < a || b < left) {
    return MAX_H;
  }
  int mid = (left + right) / 2;
  int left_min = query_min(a, b, left, mid, node * 2);
  int right_min = query_min(a, b, mid + 1, right, node * 2 + 1);
  return min(left_min, right_min);
}

int query_max(int a, int b, int left, int right, int node) {
  if (a <= left && right <= b) {
    return max_tree[node];
  }
  if (right < a || b < left) {
    return MIN_H;
  }
  int mid = (left + right) / 2;
  int left_max = query_max(a, b, left, mid, node * 2);
  int right_max = query_max(a, b, mid + 1, right, node * 2 + 1);
  return max(left_max, right_max);
}

int query(int a, int b) {
  return query_max(a, b, 0, N - 1, 1) - query_min(a, b, 0, N - 1, 1);
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
      cin >> h[i];
    }
    build();
    int a, b;
    for (int i = 0; i < Q; i++) {
      cin >> a >> b;
      cout << query(a, b) << '\n';
    }
  }
  return 0;
}
