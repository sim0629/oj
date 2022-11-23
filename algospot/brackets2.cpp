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

bool match(const string& input) {
  stack<char> s;
  for (auto c : input) {
    if (c == '(' || c == '{' || c == '[') {
      s.push(c);
      continue;
    }
    if (s.empty()) {
      return false;
    }
    if (c == ')') {
      if (s.top() != '(') {
        return false;
      }
    } else if (c == '}') {
      if (s.top() != '{') {
        return false;
      }
    } else if (c == ']') {
      if (s.top() != '[') {
        return false;
      }
    }
    s.pop();
  }
  return s.empty();
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    string input;
    cin >> input;
    cout << (match(input) ? "YES" : "NO") << '\n';
  }
  return 0;
}
