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

const int MOD = 10000000;
int memo[101][101];

int number_of_polyomino(int number_of_squares, int length_of_the_first_row) {
  if (number_of_squares == 1 || number_of_squares == length_of_the_first_row) {
    return 1;
  }
  int& ret = memo[number_of_squares][length_of_the_first_row];
  if (ret != -1) {
    return ret;
  }
  int total = 0;
  int rest_squares = number_of_squares - length_of_the_first_row;
  for (int length_of_the_second_row = 1; length_of_the_second_row <= rest_squares; length_of_the_second_row++) {
    int sub_total = number_of_polyomino(rest_squares, length_of_the_second_row) * (length_of_the_first_row + length_of_the_second_row - 1) % MOD;
    total = (total + sub_total) % MOD;
  }
  return ret = total;
}

int number_of_polyomino(int number_of_squares) {
  if (number_of_squares == 1) {
    return 1;
  }
  int total = 0;
  for (int length_of_the_first_row = 1; length_of_the_first_row <= number_of_squares; length_of_the_first_row++) {
    total = (total + number_of_polyomino(number_of_squares, length_of_the_first_row)) % MOD;
  }
  return total;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  memset(memo, -1, sizeof(memo));
  int C;
  cin >> C;
  while (C--) {
    int n;
    cin >> n;
    cout << number_of_polyomino(n) << '\n';
  }
  return 0;
}
