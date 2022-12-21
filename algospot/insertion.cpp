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

// Begin - treap implementation

typedef int KeyType;

struct Node {
  KeyType key;
  Node* left;
  Node* right;
  int priority;
  int size;

  Node(const KeyType& _key) : key(_key), left(nullptr), right(nullptr), priority(rand()), size(1) {
  }

  void setLeft(Node* _left) {
    left = _left;
    updateSize();
  }

  void setRight(Node* _right) {
    right = _right;
    updateSize();
  }

  void updateSize() {
    size = 1;
    if (left) size += left->size;
    if (right) size += right->size;
  }
};

pair<Node*, Node*> split(Node* root, const KeyType& key) {
  if (root == nullptr) return make_pair(nullptr, nullptr);
  if (root->key < key) {
    // All nodes under root->left are less than key
    Node* rightLess;
    Node* rightGreater;
    tie(rightLess, rightGreater) = split(root->right, key);
    root->setRight(rightLess);
    return make_pair(root, rightGreater);
  } else {
    Node* leftLess;
    Node* leftGreater;
    tie(leftLess, leftGreater) = split(root->left, key);
    root->setLeft(leftGreater);
    return make_pair(leftLess, root);
  }
}

Node* insert(Node* root, Node* node) {
  if (root == nullptr) return node;
  if (root->priority < node->priority) {
    Node* rootLeft;
    Node* rootRight;
    tie(rootLeft, rootRight) = split(root, node->key);
    node->setLeft(rootLeft);
    node->setRight(rootRight);
    return node;
  }
  if (root->key < node->key) {
    Node* newRight = insert(root->right, node);
    root->setRight(newRight);
  } else {
    Node* newLeft = insert(root->left, node);
    root->setLeft(newLeft);
  }
  return root;
}

Node* merge(Node* rootL, Node* rootR) {
  if (rootL == nullptr) return rootR;
  if (rootR == nullptr) return rootL;
  if (rootL->priority < rootR->priority) {
    rootR->setLeft(merge(rootL, rootR->left));
    return rootR;
  } else {
    rootL->setRight(merge(rootL->right, rootR));
    return rootL;
  }
}

Node* erase(Node* root, const KeyType& key) {
  if (root == nullptr) return root;
  if (key < root->key) {
    root->setLeft(erase(root->left, key));
    return root;
  } else if (key > root->key) {
    root->setRight(erase(root->right, key));
    return root;
  } else { // key == root->key
    Node* newRoot = merge(root->left, root->right);
    delete root;
    return newRoot;
  }
}

Node* kth(Node* root, int k) {
  int leftSize = 0;
  if (root->left) leftSize = root->left->size;
  if (k <= leftSize) return kth(root->left, k);
  if (k == leftSize + 1) return root;
  return kth(root->right, k - leftSize - 1);
}

// End - treap implementation

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    int N;
    cin >> N;
    vector<int> moves;
    Node* tree = nullptr;
    vector<int> arr;
    for (int i = 0; i < N; i++) {
      int move;
      cin >> move;
      moves.push_back(move);
      tree = insert(tree, new Node(i + 1));
    }
    for (int i = N - 1; i >= 0; i--) {
      int move = moves[i];
      Node* node = kth(tree, i - move + 1);
      arr.push_back(node->key);
      tree = erase(tree, node->key);
    }
    for (int i = N - 1; i >= 0; i--) {
      cout << arr[i] << (i > 0 ? ' ' : '\n');
    }
  }
  return 0;
}
