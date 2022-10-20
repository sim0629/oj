#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

const int MOD = 1000000007;
int answers[101];

void calc() {
  answers[0] = 1;
  answers[1] = 1;
  for (int i = 2; i <= 100; i++) {
    answers[i] = (answers[i - 2] + answers[i - 1]) % MOD;
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  calc();
  int C;
  cin >> C;
  while (C--) {
    int n;
    cin >> n;
    if (n < 3) {
      cout << 0;
    } else if (n % 2 == 1) {
      cout << (answers[n] - answers[n / 2] + MOD) % MOD;
    } else {
      cout << (((answers[n] - answers[n / 2] + MOD) % MOD) - answers[n / 2 - 1] + MOD) % MOD;
    }
    cout << '\n';
  }
  return 0;
}
