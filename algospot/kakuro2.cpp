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

struct Hint {
  int y;
  int x;
  int dir;
  int sum;
  vector<pair<int, int>> coords;
  Hint(int _y, int _x, int _dir, int _sum) : y(_y), x(_x), dir(_dir), sum(_sum) {}
};

int N;
int bw[20][20];
int board[20][20];
vector<int> board_to_hints[20][20];
int Q;
vector<Hint> hints;

bool is_okay(int q, int y, int x, int digit) {
  auto& hint = hints[q];
  bool used[10] = {};
  int used_sum = 0;
  for (auto& coord : hint.coords) {
    int v = board[coord.first][coord.second];
    used[v] = true;
    used_sum += v;
  }

  if (used[digit]) return false;

  int empty_cnt = 0;
  for (auto& coord : hint.coords) {
    if (coord.first == y && coord.second == x) continue;
    if (board[coord.first][coord.second]) continue;
    empty_cnt++;
  }

  int remain = empty_cnt;
  int remain_sum = 0;
  for (int remain_digit = 1; remain_digit <= 9 && remain > 0; remain_digit++) {
    if (remain_digit != digit && !used[remain_digit]) {
      remain_sum += remain_digit;
      remain--;
    }
  }
  if (digit + used_sum + remain_sum > hint.sum) {
    return false;
  }

  remain = empty_cnt;
  remain_sum = 0;
  for (int remain_digit = 9; remain_digit >= 1 && remain > 0; remain_digit++) {
    if (remain_digit != digit && !used[remain_digit]) {
      remain_sum += remain_digit;
      remain--;
    }
  }
  if (digit + used_sum + remain_sum < hint.sum) {
    return false;
  }

  return true;
}

bool solve_hint(int q, int idx) {
  if (q >= Q) return true;
  auto& hint = hints[q];
  if (idx >= hint.coords.size()) {
    return solve_hint(q + 1, 0);
  }
  auto& coord = hint.coords[idx];
  if (board[coord.first][coord.second]) return solve_hint(q, idx + 1);
  for (int digit = 1; digit <= 9; digit++) {
    if (!is_okay(q, coord.first, coord.second, digit)) continue;
    bool others_okay = true;
    for (int qq : board_to_hints[coord.first][coord.second]) {
      if (qq <= q) continue;
      if (!is_okay(qq, coord.first, coord.second, digit)) {
        others_okay = false;
        break;
      }
    }
    if (!others_okay) continue;

    board[coord.first][coord.second] = digit;
    if (solve_hint(q, idx + 1)) {
      return solve_hint(q + 1, 0);
    }
    board[coord.first][coord.second] = 0;
  }
  return false;
}

void solve() {
  solve_hint(0, 0);
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int T;
  cin >> T;
  while (T--) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> bw[i][j];
        board[i][j] = 0;
        board_to_hints[i][j].clear();
      }
    }
    hints.clear();
    cin >> Q;
    for (int q = 0; q < Q; q++) {
      int y, x, dir, sum;
      cin >> y >> x >> dir >> sum;
      y--; x--;
      auto hint = Hint(y, x, dir, sum);
      if (dir == 0) { // horizontal
        int i = y;
        for (int j = x + 1; j < N; j++) {
          if (bw[i][j] == 0) break;
          hint.coords.emplace_back(i, j);
          board_to_hints[i][j].push_back(q);
        }
      } else { // vertical
        int j = x;
        for (int i = y + 1; y < N; i++) {
          if (bw[i][j] == 0) break;
          hint.coords.emplace_back(i, j);
          board_to_hints[i][j].push_back(q);
        }
      }
      hints.push_back(hint);
    }
    solve();
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << board[i][j];
        if (j + 1 < N) cout << ' ';
      }
      cout << '\n';
    }
  }
  return 0;
}
