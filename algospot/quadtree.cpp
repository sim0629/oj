#include <iostream>
#include <vector>

using namespace std;

struct Node {
  char color;
  vector<Node> children;
};

Node buildNode(const string& treeCode, int& index) {
  Node node;
  node.color = treeCode[index];
  index++;
  if (node.color == 'x') {
    node.children.push_back(buildNode(treeCode, index));
    node.children.push_back(buildNode(treeCode, index));
    node.children.push_back(buildNode(treeCode, index));
    node.children.push_back(buildNode(treeCode, index));
  }
  return node;
}

Node buildTree(const string& treeCode) {
  int index = 0;
  return buildNode(treeCode, index);
}

void traverseNode(const Node& node) {
  cout << node.color;
  if (node.children.empty()) {
    return;
  }
  traverseNode(node.children[2]);
  traverseNode(node.children[3]);
  traverseNode(node.children[0]);
  traverseNode(node.children[1]);
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    string treeCode;
    cin >> treeCode;
    Node tree = buildTree(treeCode);
    traverseNode(tree);
    cout << '\n';
  }
  return 0;
}
