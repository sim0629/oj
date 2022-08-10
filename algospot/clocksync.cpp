#include <iostream>
#include <vector>

using namespace std;

const int NUM_OF_CLOCKS = 16;

const vector<int> S0 = {0, 1, 2};
const vector<int> S1 = {3, 7, 9, 11};
const vector<int> S2 = {4, 10, 14, 15};
const vector<int> S3 = {0, 4, 5, 6, 7};
const vector<int> S4 = {6, 7, 8, 10, 12};
const vector<int> S5 = {0, 2, 14, 15};
const vector<int> S6 = {3, 14, 15};
const vector<int> S7 = {4, 5, 7, 14, 15};
const vector<int> S8 = {1, 2, 3, 4, 5};
const vector<int> S9 = {3, 4, 5, 9, 13};

bool isAllZeros(vector<int>& clocks) {
  for (int clock : clocks) {
    if (clock != 0) {
      return false;
    }
  }
  return true;
}

int moves(vector<int>& clocks) {
  int minMoves = -1;
  for (int i0 = 0; i0 < 4; i0++) {
    for (int i1 = 0; i1 < 4; i1++) {
      for (int i2 = 0; i2 < 4; i2++) {
        for (int i3 = 0; i3 < 4; i3++) {
          for (int i4 = 0; i4 < 4; i4++) {
            for (int i5 = 0; i5 < 4; i5++) {
              for (int i6 = 0; i6 < 4; i6++) {
                for (int i7 = 0; i7 < 4; i7++) {
                  for (int i8 = 0; i8 < 4; i8++) {
                    for (int i9 = 0; i9 < 4; i9++) {
                      if (isAllZeros(clocks)) {
                        int i = i0 + i1 + i2 + i3 + i4 + i5 + i6 + i7 + i8 + i9;
                        if (minMoves == -1 || i < minMoves) {
                          minMoves = i;
                        }
                      }
                      for (int c : S9) clocks[c] = (clocks[c] + 1) % 4;
                    }
                    for (int c : S8) clocks[c] = (clocks[c] + 1) % 4;
                  }
                  for (int c : S7) clocks[c] = (clocks[c] + 1) % 4;
                }
                for (int c : S6) clocks[c] = (clocks[c] + 1) % 4;
              }
              for (int c : S5) clocks[c] = (clocks[c] + 1) % 4;
            }
            for (int c : S4) clocks[c] = (clocks[c] + 1) % 4;
          }
          for (int c : S3) clocks[c] = (clocks[c] + 1) % 4;
        }
        for (int c : S2) clocks[c] = (clocks[c] + 1) % 4;
      }
      for (int c : S1) clocks[c] = (clocks[c] + 1) % 4;
    }
    for (int c : S0) clocks[c] = (clocks[c] + 1) % 4;
  }
  return minMoves;
}

void solve() {
  int C;
  cin >> C;
  while (C--) {
    vector<int> clocks;
    for (int i = 0; i < NUM_OF_CLOCKS; i++) {
      int clock;
      cin >> clock;
      clocks.push_back(clock / 3 % 4); // {12=>0, 3=>1, 6=>2, 9=>3}
    }
    cout << moves(clocks) << '\n';
  }
}

int main(void) {
  ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  solve();
  return 0;
}
