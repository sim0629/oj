#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int n, d, p;
vector<int> g[50];
double prob[50][101];

void calcProb() {
  for (int ni = 0; ni < n; ni++) {
    prob[ni][0] = ni == p ? 1.0 : 0.0;
  }
  for (int di = 1; di <= d; di++) {
    for (int ni = 0; ni < n; ni++) {
      prob[ni][di] = 0.0;
    }
    for (int ni = 0; ni < n; ni++) {
      double mProb = prob[ni][di - 1] / (double)g[ni].size();
      for (int mi : g[ni]) {
        prob[mi][di] += mProb;
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  cout.precision(8);
  int c;
  cin >> c;
  while (c--) {
    cin >> n >> d >> p;
    for (int i = 0; i < n; i++) {
      g[i].clear();
      for (int j = 0; j < n; j++) {
        int ox;
        cin >> ox;
        if (ox) {
          g[i].push_back(j);
        }
      }
    }
    calcProb();
    int t;
    cin >> t;
    while (t--) {
      int q;
      cin >> q;
      cout << prob[q][d];
      if (t) cout << ' ';
    }
    cout << '\n';
  }
  return 0;
}
