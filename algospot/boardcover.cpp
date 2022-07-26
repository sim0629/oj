#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//  ##  ##  .#  #.
//  #.  .#  ##  ##

int C;
int H, W;
char grid[20][20];

int place(int moves) {
  if (moves == 0) return 1;
  for (int h = 0; h < H; h++) {
    for (int w = 0; w < W; w++) {
      if (grid[h][w] == '.') {
        int total = 0;
        if (w + 1 < W && h + 1 < H && grid[h][w + 1] == '.' && grid[h + 1][w] == '.') {
          grid[h][w] = grid[h][w + 1] = grid[h + 1][w] = '#';
          total += place(moves - 1);
          grid[h][w] = grid[h][w + 1] = grid[h + 1][w] = '.';
        }
        if (w + 1 < W && h + 1 < H && grid[h][w + 1] == '.' && grid[h + 1][w + 1] == '.') {
          grid[h][w] = grid[h][w + 1] = grid[h + 1][w + 1] = '#';
          total += place(moves - 1);
          grid[h][w] = grid[h][w + 1] = grid[h + 1][w + 1] = '.';
        }
        if (w - 1 >= 0 && h + 1 < H && grid[h + 1][w - 1] == '.' && grid[h + 1][w] == '.') {
          grid[h][w] = grid[h + 1][w - 1] = grid[h + 1][w] = '#';
          total += place(moves - 1);
          grid[h][w] = grid[h + 1][w - 1] = grid[h + 1][w] = '.';
        }
        if (w + 1 < W && h + 1 < H && grid[h + 1][w] == '.' && grid[h + 1][w + 1] == '.') {
          grid[h][w] = grid[h + 1][w] = grid[h + 1][w + 1] = '#';
          total += place(moves - 1);
          grid[h][w] = grid[h + 1][w] = grid[h + 1][w + 1] = '.';
        }
        return total;
      }
    }
  }
  return 0; // impossible
}

int main(void) {
  cin >> C;
  while (C-- > 0) {
    cin >> H >> W;
    fill(&grid[0][0], &grid[0][0] + 20 * 20, 0);
    for (int h = 0; h < H; h++) {
      string s;
      cin >> s;
      copy(s.begin(), s.end(), &grid[h][0]);
    }

    int emptyCells = 0;
    for (int h = 0; h < H; h++) {
      for (int w = 0; w < W; w++) {
        if (grid[h][w] == '.') {
          emptyCells++;
        }
      }
    }
    if (emptyCells % 3 != 0) {
      cout << 0;
    } else {
      cout << place(emptyCells / 3);
    }
    cout << '\n';
  }
  return 0;
}
