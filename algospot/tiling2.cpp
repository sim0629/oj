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

int answers[101];

void calc() {
  answers[0] = 1;
  answers[1] = 1;
  for (int i = 2; i <= 100; i++) {
    answers[i] = (answers[i - 2] + answers[i - 1]) % 1000000007;
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
    cout << answers[n] << '\n';
  }
  return 0;
}
