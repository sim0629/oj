#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
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
vector<int> preorder;
vector<int> inorder;
unordered_map<int, int> lchild;
unordered_map<int, int> rchild;

void construct_tree(int preorder_from, int preorder_to, int inorder_from, int inorder_to) {
  if (preorder_from == preorder_to) {
    return;
  }
  int root = preorder[preorder_from];
  for (int i = inorder_from; i <= inorder_to; i++) {
    if (inorder[i] == root) {
      int n_left = i - inorder_from;
      if (n_left > 0) {
        lchild[root] = preorder[preorder_from + 1];
        construct_tree(preorder_from + 1, preorder_from + n_left, inorder_from, i - 1);
      }
      int n_right = inorder_to - i;
      if (n_right > 0) {
        rchild[root] = preorder[preorder_from + n_left + 1];
        construct_tree(preorder_from + n_left + 1, preorder_to, i + 1, inorder_to);
      }
      break;
    }
  }
}

void construct_tree() {
  lchild.clear();
  rchild.clear();
  construct_tree(0, N - 1, 0, N - 1);
}

void traverse_postorder(int node, vector<int>& out) {
  if (lchild.find(node) != lchild.end()) {
    traverse_postorder(lchild[node], out);
  }
  if (rchild.find(node) != rchild.end()) {
    traverse_postorder(rchild[node], out);
  }
  out.push_back(node);
}

vector<int> traverse_postorder() {
  vector<int> postorder;
  traverse_postorder(preorder[0], postorder);
  return postorder;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    cin >> N;
    preorder.clear();
    for (int i = 0; i < N; i++) {
      int v;
      cin >> v;
      preorder.push_back(v);
    }
    inorder.clear();
    for (int i = 0; i < N; i++) {
      int v;
      cin >> v;
      inorder.push_back(v);
    }
    construct_tree();
    vector<int> postorder = traverse_postorder();
    for (int i = 0; i < N; i++) {
      cout << postorder[i] << (i < N - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
