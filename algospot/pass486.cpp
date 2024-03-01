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

bool is_not_prime[10000001] = {false};
vector<int> primes;

void precalc_primes() {
  is_not_prime[1] = true;
  for (int i = 2; i <= 10000000; i++) {
    if (is_not_prime[i]) continue;
    primes.push_back(i);
    for (int j = i + i; j <= 10000000; j += i) {
      is_not_prime[j] = true;
    }
  }
}

unordered_map<int, int> memo;

int number_of_divisors(int n) {
  if (n == 1) return 1;
  if (!is_not_prime[n]) return 2;
  if (memo.find(n) != memo.end()) {
    return memo[n];
  }
  for (int prime : primes) {
    int count = 0;
    while (n % prime == 0) {
      n /= prime;
      count++;
    }
    return memo[n] = ((count + 1) * number_of_divisors(n));
  }
  return 1; // impossible
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  precalc_primes();
  int c;
  cin >> c;
  while (c--) {
    int n, lo, hi;
    cin >> n >> lo >> hi;
    int count = 0;
    for (int x = lo; x <= hi; x++) {
      if (number_of_divisors(x) == n) {
        count++;
      }
    }
    cout << count << '\n';
  }
  return 0;
}
