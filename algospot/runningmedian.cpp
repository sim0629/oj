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

const int MOD = 20090711;
int N, a, b;
set<int> lset, rset;

void insertA(int A) {
  if (rset.empty()) {
    rset.insert(A);
    return;
  }
  if (A < *rset.begin()) {
    lset.insert(A);
  } else {
    rset.insert(A);
  }
  if (lset.size() + 1 < rset.size()) {
    int Ai = *rset.begin();
    rset.erase(rset.begin());
    lset.insert(Ai);
  } else  if (lset.size() > rset.size()) {
    int Ai = *prev(lset.end());
    lset.erase(prev(lset.end()));
    rset.insert(Ai);
  } else {
    // do nothing
  }
}

int getMedian() {
  if (lset.size() < rset.size()) {
    return *rset.begin();
  } else {
    return *lset.rbegin();
  }
}

int sumOfMedians() {
  lset.clear();
  rset.clear();
  int A = 1983;
  int S = 0;
  for (int i = 0; i < N; i++) {
    insertA(A);
    S = (S + getMedian()) % MOD;
    A = (int)(((long long)A * a + b) % MOD);
  }
  return S;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N >> a >> b;
    cout << sumOfMedians() << '\n';
  }
  return 0;
}
