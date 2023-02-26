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

const int INF = 987654321;
int V;
int W;
vector<pair<int, int>> holes[100];
bool reachable[100][100];
int dist[100];

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> V >> W;
    for (int v = 0; v < V; v++) {
      holes[v].clear();
    }
    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
        reachable[i][j] = (i == j);
      }
    }
    for (int i = 0; i < W; i++) {
      int a, b, d;
      cin >> a >> b >> d;
      holes[a].emplace_back(b, d);
      reachable[a][b] = true;
    }
    for (int k = 0; k < V; k++) {
      for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
          if (reachable[i][k] && reachable[k][j]) {
            reachable[i][j] = true;
          }
        }
      }
    }
    // minimum
    dist[0] = 0;
    for (int i = 1; i < V; i++) {
      dist[i] = INF;
    }
    for (int k = 0; k < V - 1; k++) {
      bool updated = false;
      for (int here = 0; here < V; here++) {
        for (auto p : holes[here]) {
          int there;
          int d;
          tie(there, d) = p;
          if (dist[there] > dist[here] + d) {
            dist[there] = dist[here] + d;
            updated = true;
          }
        }
      }
      if (!updated) {
        break;
      }
    }
    bool infinite = false;
    for (int here = 0; here < V; here++) {
      for (auto p : holes[here]) {
        int there;
        int d;
        tie(there, d) = p;
        if (dist[there] > dist[here] + d) {
          if (reachable[0][here] && reachable[here][1]) {
            infinite = true;
            break;
          }
        }
      }
    }
    if (infinite) {
      cout << "INFINITY";
    } else if (dist[1] > INF - 1000000) {
      cout << "UNREACHABLE\n";
      continue;
    } else {
      cout << dist[1];
    }
    cout << ' ';
    // maximum
    dist[0] = 0;
    for (int i = 1; i < V; i++) {
      dist[i] = INF;
    }
    for (int k = 0; k < V - 1; k++) {
      bool updated = false;
      for (int here = 0; here < V; here++) {
        for (auto p : holes[here]) {
          int there;
          int d;
          tie(there, d) = p;
          d = -d;
          if (dist[there] > dist[here] + d) {
            dist[there] = dist[here] + d;
            updated = true;
          }
        }
      }
      if (!updated) {
        break;
      }
    }
    infinite = false;
    for (int here = 0; here < V; here++) {
      for (auto p : holes[here]) {
        int there;
        int d;
        tie(there, d) = p;
        d = -d;
        if (dist[there] > dist[here] + d) {
          if (reachable[0][here] && reachable[here][1]) {
            infinite = true;
            break;
          }
        }
      }
    }
    if (infinite) {
      cout << "INFINITY";
    } else if (dist[1] > INF - 1000000) {
      // impossible
    } else {
      cout << -dist[1];
    }
    cout << '\n';
  }
  return 0;
}
