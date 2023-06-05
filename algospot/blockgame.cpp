#include <algorithm>
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

unordered_map<int, bool> memo; // winning?

struct Board {
  char v[5][6];

  int key() {
    int k = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        k <<= 1;
        k |= (v[i][j] == '.' ? 0 : 1);
      }
    }
    return k;
  }

  bool lost() {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        // ##
        // #.
        if (v[i + 0][j + 0] == '.' && v[i + 0][j + 1] == '.' && v[i + 1][j + 0] == '.') {
          return false;
        }
        // ##
        // .#
        if (v[i + 0][j + 0] == '.' && v[i + 0][j + 1] == '.' && v[i + 1][j + 1] == '.') {
          return false;
        }
        // .#
        // ##
        if (v[i + 0][j + 1] == '.' && v[i + 1][j + 0] == '.' && v[i + 1][j + 1] == '.') {
          return false;
        }
        // #.
        // ##
        if (v[i + 0][j + 0] == '.' && v[i + 1][j + 0] == '.' && v[i + 1][j + 1] == '.') {
          return false;
        }
      }
    }
    // ##
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 4; j++) {
        if (v[i][j] == '.' && v[i][j + 1] == '.') {
          return false;
        }
      }
    }
    // #
    // #
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        if (v[i][j] == '.' && v[i + 1][j] == '.') {
          return false;
        }
      }
    }
    return true;
  }

  bool can_win() {
    int k = key();
    if (memo.find(k) != memo.end()) {
      return memo[k];
    }

    if (lost()) {
      return memo[k] = false;
    }

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        // ##
        // #.
        if (v[i + 0][j + 0] == '.' && v[i + 0][j + 1] == '.' && v[i + 1][j + 0] == '.') {
          v[i][j] = v[i][j + 1] = v[i + 1][j] = '#';
          bool other = can_win();
          v[i][j] = v[i][j + 1] = v[i + 1][j] = '.';
          if (!other) {
            return memo[k] = true;
          }
        }
        // ##
        // .#
        if (v[i + 0][j + 0] == '.' && v[i + 0][j + 1] == '.' && v[i + 1][j + 1] == '.') {
          v[i][j] = v[i][j + 1] = v[i + 1][j + 1] = '#';
          bool other = can_win();
          v[i][j] = v[i][j + 1] = v[i + 1][j + 1] = '.';
          if (!other) {
            return memo[k] = true;
          }
        }
        // .#
        // ##
        if (v[i + 0][j + 1] == '.' && v[i + 1][j + 0] == '.' && v[i + 1][j + 1] == '.') {
          v[i][j + 1] = v[i + 1][j] = v[i + 1][j + 1] = '#';
          bool other = can_win();
          v[i][j + 1] = v[i + 1][j] = v[i + 1][j + 1] = '.';
          if (!other) {
            return memo[k] = true;
          }
        }
        // #.
        // ##
        if (v[i + 0][j + 0] == '.' && v[i + 1][j + 0] == '.' && v[i + 1][j + 1] == '.') {
          v[i][j] = v[i + 1][j] = v[i + 1][j + 1] = '#';
          bool other = can_win();
          v[i][j] = v[i + 1][j] = v[i + 1][j + 1] = '.';
          if (!other) {
            return memo[k] = true;
          }
        }
      }
    }
    // ##
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 4; j++) {
        if (v[i][j] == '.' && v[i][j + 1] == '.') {
          v[i][j] = v[i][j + 1] = '#';
          bool other = can_win();
          v[i][j] = v[i][j + 1] = '.';
          if (!other) {
            return memo[k] = true;
          }
        }
      }
    }
    // #
    // #
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 5; j++) {
        if (v[i][j] == '.' && v[i + 1][j] == '.') {
          v[i][j] = v[i + 1][j] = '#';
          bool other = can_win();
          v[i][j] = v[i + 1][j] = '.';
          if (!other) {
            return memo[k] = true;
          }
        }
      }
    }
    return memo[k] = false;
  }
};

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    Board board;
    for (int i = 0; i < 5; i++) {
      cin >> board.v[i];
    }
    cout << (board.can_win() ? "WINNING" : "LOSING") << '\n';
  }
  return 0;
}
