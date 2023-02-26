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

unordered_map<string, int> steps;

void construct_graph(const string &init) {
  queue<string> q;
  q.push(init);
  steps[init] = 0;
  while (!q.empty()) {
    string s = q.front();
    q.pop();
    for (int flip_length = 2; flip_length <= s.length(); flip_length++) {
      for (int start_index = 0; start_index + flip_length <= s.length(); start_index++) {
        string t;
        for (int i = 0; i < start_index; i++) {
          t.push_back(s[i]);
        }
        for (int i = start_index; i < start_index + flip_length; i++) {
          t.push_back(s[(start_index + flip_length - 1) - (i - start_index)]);
        }
        for (int i = start_index + flip_length; i < s.length(); i++) {
          t.push_back(s[i]);
        }
        if (steps.find(t) != steps.end()) {
          continue;
        }
        q.push(t);
        steps[t] = steps[s] + 1;
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  construct_graph("12345678");
  construct_graph("1234567");
  construct_graph("123456");
  construct_graph("12345");
  construct_graph("1234");
  construct_graph("123");
  construct_graph("12");
  construct_graph("1");
  int C;
  cin >> C;
  while (C--) {
    int N;
    cin >> N;
    vector<int> input_arr_copy;
    vector<int> input_arr;
    map<int, char> rank;
    for (int i = 0; i < N; i++) {
      int a;
      cin >> a;
      input_arr.push_back(a);
    }
    input_arr_copy = input_arr;
    sort(input_arr.begin(), input_arr.end());
    for (int i = 0; i < N; i++) {
      rank[input_arr[i]] = '1' + i;
    }
    string w;
    for (int i = 0; i < N; i++) {
      w.push_back(rank[input_arr_copy[i]]);
    }
    cout << steps[w] << '\n';
  }
  return 0;
}
