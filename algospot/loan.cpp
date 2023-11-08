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
    double N, M, P;
    cin >> N >> M >> P;
    double q = 1 + P / 1200;
    double C = (1 - q) * pow(q, M) / (1 - pow(q, M)) * N;
    cout << fixed;
    cout.precision(10);
    cout << C << '\n';
  }
  return 0;
}
