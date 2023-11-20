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

vector<int> primes;

void precalc_primes() {
  bool is_not_prime[1001] = {false};
  for (int i = 2; i <= 1000; i++) {
    if (is_not_prime[i]) continue;
    primes.push_back(i);
    for (int j = i + i; j <= 1000; j += i) {
      is_not_prime[j] = true;
    }
  }
}

bool divisible(const vector<int>& numbers, int p) {
  for (int number : numbers) {
    if (number % p != 0) {
      return false;
    }
  }
  return true;
}

void divide(vector<int>& numbers) {
  for (int prime : primes) {
    while (divisible(numbers, prime)) {
      for (int i = 0; i < numbers.size(); i++) {
        numbers[i] = numbers[i] / prime;
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  precalc_primes();
  int c;
  cin >> c;
  while (c--) {
    int n;
    cin >> n;
    vector<int> ri, pi;
    for (int i = 0; i < n; i++) {
      int r;
      cin >> r;
      ri.push_back(r);
    }
    for (int i = 0; i < n; i++) {
      int p;
      cin >> p;
      pi.push_back(p);
    }

    divide(ri);
    int max_mul = 1;
    for (int i = 0; i < n; i++) {
      int mul = pi[i] / ri[i] + (pi[i] % ri[i] == 0 ? 0: 1);
      max_mul = max(max_mul, mul);
    }
    for (int i = 0; i < n; i++) {
       cout << ri[i] * max_mul - pi[i];
       cout << (i + 1 < n ? ' ' : '\n');
    }
  }
  return 0;
}
