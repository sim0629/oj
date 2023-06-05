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

struct Board {
  char v[3][3];

  int key() {
    int k = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        k <<= 2;
        if (v[i][j] == 'x') {
          k += 1;
        } else if (v[i][j] == 'o') {
          k += 2;
        }
      }
    }
    return k;
  }

  bool win(char c) {
    bool w;
    for (int i = 0; i < 3; i++) {
      w = true;
      for (int j = 0; j < 3; j++) {
        if (v[i][j] != c) {
          w = false;
          break;
        }
      }
      if (w) {
        return true;
      }
    }
    for (int i = 0; i < 3; i++) {
      w = true;
      for (int j = 0; j < 3; j++) {
        if (v[j][i] != c) {
          w = false;
          break;
        }
      }
      if (w) {
        return true;
      }
    }
    w = true;
    for (int i = 0; i < 3; i++) {
      if (v[i][i] != c) {
        w = false;
        break;
      }
    }
    if (w) {
      return true;
    }
    w = true;
    for (int i = 0; i < 3; i++) {
      if (v[i][2 - i] != c) {
        w = false;
        break;
      }
    }
    if (w) {
      return true;
    }
    return false;
  }

  bool tie() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (v[i][j] != 'x' && v[i][j] != 'o') {
          return false;
        }
      }
    }
    return true;
  }

  bool is_x_turn() {
    int x_count = 0;
    int o_count = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (v[i][j] == 'x') {
          x_count++;
        } else if (v[i][j] == 'o') {
          o_count++;
        }
      }
    }
    return o_count >= x_count;
  }
};

unordered_map<int, char> memo;

char winner(Board board) {
  int key = board.key();
  if (memo.find(key) != memo.end()) {
    return memo[key];
  }
  if (board.win('x')) {
    memo[key] = 'x';
    return 'x';
  }
  if (board.win('o')) {
    memo[key] = 'o';
    return 'o';
  }
  if (board.tie()) {
    memo[key] = 't';
    return 't';
  }
  bool x_turn = board.is_x_turn();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board.v[i][j] != 'x' && board.v[i][j] != 'o') {
        Board next_board = board;
        next_board.v[i][j] = x_turn ? 'x' : 'o';
        char next_winner = winner(next_board);
        if (x_turn && next_winner == 'x') {
          memo[key] = 'x';
          return 'x';
        }
        if (!x_turn && next_winner == 'o') {
          memo[key] = 'o';
          return 'o';
        }
      }
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board.v[i][j] != 'x' && board.v[i][j] != 'o') {
        Board next_board = board;
        next_board.v[i][j] = x_turn ? 'x' : 'o';
        char next_winner = winner(next_board);
        if (next_winner == 't') {
          memo[key] = 't';
          return 't';
        }
      }
    }
  }
  if (x_turn) {
    memo[key] = 'o';
    return 'o';
  } else {
    memo[key] = 'x';
    return 'x';
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    char buf[3][10];
    cin >> buf[0] >> buf[1] >> buf[2];
    Board board;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board.v[i][j] = buf[i][j];
      }
    }
    char result = winner(board);
    if (result == 't') {
      cout << "TIE";
    } else {
      cout << result;
    }
    cout << '\n';
  }
  return 0;
}
