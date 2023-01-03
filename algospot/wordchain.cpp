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

int N;
vector<string> words;

vector<int> graph[100];

void construct_graph() {
  for (int i = 0; i < N; i++) {
    graph[i].clear();
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      if (words[i][words[i].size() - 1] == words[j][0]) {
        graph[i].push_back(j);
      }
    }
  }
}

int visited[100];
int found;

void traverse(int cur, vector<int>& path) {
  visited[cur] = 1;
  path.push_back(cur);
  if (path.size() == N) {
    found = 1;
    return;
  }
  for (auto next : graph[cur]) {
    if (visited[next]) continue;
    traverse(next, path);
    if (found) {
      return;
    }
  }
  path.pop_back();
  visited[cur] = 0;
}

void solve() {
  for (int i = 0; i < N; i++) {
    vector<int> path;
    for (int i = 0; i < N; i++) {
      visited[i] = 0;
    }
    found = 0;
    traverse(i, path);
    if (found) {
      for (auto idx : path) {
        cout << words[idx] << ' ';
      }
      cout << '\n';
      break;
    }
  }
  if (!found) {
    cout << "IMPOSSIBLE\n";
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N;
    words.clear();
    for (int i = 0; i < N; i++) {
      string s;
      cin >> s;
      words.push_back(s);
    }
    construct_graph();
    solve();
  }
  return 0;
}
