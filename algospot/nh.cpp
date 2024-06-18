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

int N, M;
char patterns[100][12];

const int ALPHA = 26;
const int MOD = 10007;

struct Trie {
  Trie* children[ALPHA];
  bool terminal;

  Trie* fail;
  int output;
  int no;
  Trie* next[ALPHA];

  Trie() {
    memset(children, 0, sizeof(children));
    terminal = false;

    fail = nullptr;
    output = 0;
    no = -1;
    memset(next, 0, sizeof(next));
  }

  ~Trie() {
    for (int i = 0; i < ALPHA; i++) {
      if (children[i]) {
        delete children[i];
      }
    }
  }

  void insert(const char* s) {
    char c = *s;
    if (c == '\0') {
      this->terminal = true;
      return;
    }
    int next = c - 'a';
    if (!children[next]) children[next] = new Trie();
    children[next]->insert(s + 1);
  }

  Trie* get_next(int i) {
    if (next[i]) {
      return next[i];
    }
    Trie* t = this;
    while (t != t->fail && t->children[i] == nullptr) {
      t = t->fail;
    }
    if (t->children[i]) t = t->children[i];
    return next[i] = t;
  }
};

void compute_failure(Trie* root) {
  int no = 0;
  queue<Trie*> q;
  root->fail = root;
  root->no = no; no++;
  q.push(root);
  while (!q.empty()) {
    Trie* here = q.front();
    q.pop();
    for (int i = 0; i < ALPHA; i++) {
      Trie* child = here->children[i];
      if (!child) {
        continue;
      }
      if (here == root) {
        child->fail = root;
      } else {
        Trie* t = here->fail;
        while (true) {
          if (t->children[i]) {
            t = t->children[i];
            break;
          } else {
            if (t == root) {
              break;
            }
            t = t->fail;
          }
        }
        child->fail = t;
      }
      child->output = child->fail->output;
      if (child->terminal) child->output += 1;
      child->no = no; no++;
      q.push(child);
    }
  }
}

Trie* build_trie() {
  Trie* root = new Trie();
  for (int i = 0; i < M; i++) {
    root->insert(patterns[i]);
  }
  compute_failure(root);
  return root;
}

int memo[101][1001];

int count(int length, Trie* state) {
  if (state->output > 0) return 0;
  if (length == 0) return 1;

  int& ret = memo[length][state->no];
  if (ret != -1) {
    return ret;
  }
  int acc = 0;
  for (int i = 0; i < ALPHA; i++) {
    Trie* next = state->get_next(i);
    acc += count(length - 1, next);
    acc %= MOD;
  }
  return ret = acc;
}

void reset_memo() {
  for (int i = 0; i < 101; i++) {
    for (int j = 0; j < 1001; j++) {
      memo[i][j] = -1;
    }
  }
}

int solve() {
  Trie* trie = build_trie();
  reset_memo();
  int ans = count(N, trie);
  delete trie;
  return ans;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
      cin >> patterns[i];
    }
    cout << solve() << '\n';
  }
  return 0;
}
