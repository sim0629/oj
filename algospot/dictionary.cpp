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

int graph[26][26];
int indeg[26];
int visited[26];

void topo() {
  memset(indeg, 0, sizeof(indeg));
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26; j++) {
      if (graph[i][j]) {
        indeg[j]++;
      }
    }
  }

  queue<int> q;
  for (int i = 0; i < 26; i++) {
    visited[i] = 0;
    if (indeg[i] == 0) {
      q.push(i);
    }
  }

  vector<int> seq;
  while (!q.empty()) {
    int node = q.front();
    q.pop();
    seq.push_back(node);
    visited[node] = 1;
    for (int next = 0; next < 26; next++) {
      if (!visited[next] && graph[node][next]) {
        indeg[next]--;
        if (indeg[next] == 0) {
          q.push(next);
        }
      }
    }
  }

  if (seq.size() == 26) {
    for (int node : seq) {
      cout << (char)('a' + node);
    }
    cout << '\n';
  } else {
    cout << "INVALID HYPOTHESIS\n";
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    memset(graph, 0, sizeof(graph));
    int N;
    cin >> N;
    string prev_word;
    cin >> prev_word;
    for (int i = 1; i < N; i++) {
      string curr_word;
      cin >> curr_word;
      for (int j = 0; j < prev_word.size() && j < curr_word.size(); j++) {
        if (prev_word[j] != curr_word[j]) {
          graph[prev_word[j] - 'a'][curr_word[j] - 'a'] = 1;
          break;
        }
      }
      prev_word = curr_word;
    }
    topo();
  }
  return 0;
}
