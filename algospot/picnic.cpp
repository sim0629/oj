#include <iostream>

using namespace std;

int C;
int n, m;
bool friends[10][10];
bool occupied[10];

int occupy(int pairsLeft) {
  int x = -1;
  int y = -1;
  if (pairsLeft == 1) {
    for (int i = 0; i < n; i++) {
      if (!occupied[i]) {
        if (x == -1) x = i;
        else y = i;
      }
    }
    return friends[x][y] ? 1 : 0;
  }
  for (x = 0; x < n; x++) {
    if (!occupied[x]) break;
  }
  int total = 0;
  for (int y = x + 1; y < n; y++) {
    if (occupied[y]) continue;
    if (!friends[x][y]) continue;
    occupied[x] = occupied[y] = true;
    total += occupy(pairsLeft - 1);
    occupied[x] = occupied[y] = false;
  }
  return total;
}

int main(void) {
  cin >> C;
  while (C-- > 0) {
    cin >> n >> m;
    fill(&friends[0][0], &friends[0][0] + 10 * 10, false);
    fill(&occupied[0], &occupied[0] + 10, false);
    while (m-- > 0) {
      int x, y;
      cin >> x >> y;
      friends[x][y] = true;
      friends[y][x] = true;
    }
    cout << occupy(n / 2) << '\n';
  }
  return 0;
}
