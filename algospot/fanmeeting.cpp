#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

const int CHUNK_SIZE = 32;

vector<int> getChunks(const string& s, int offset) {
  vector<int> chunks;
  if (offset >= s.size()) {
    chunks.push_back(0);
  } else {
    string::const_iterator iter = next(s.begin(), offset);
    while (iter != s.end()) {
      int chunk = 0;
      for (int i = 0; i < CHUNK_SIZE; i++) {
        chunk |= (iter != s.end() && (*iter) == 'M' ? 1 : 0);
        if (i + 1 < CHUNK_SIZE) {
          chunk <<= 1;
        }
        if (iter != s.end()) {
          iter++;
        }
      }
      chunks.push_back(chunk);
    }
  }
  return chunks;
}

int solve(const string& members, const string& fans) {
  vector<int> memberChunks = getChunks(members, 0);
  vector<vector<int>> fanChunksByOffset;
  for (int offset = 0; offset < CHUNK_SIZE; offset++) {
    fanChunksByOffset.push_back(getChunks(fans, offset));
  }

  int totalHugs = 0;
  for (int pos = 0; pos < fans.size() - members.size() + 1; pos++) {
    const vector<int>& fanChunks = fanChunksByOffset[pos % CHUNK_SIZE];
    bool fail = false;
    for (int i = 0; i < memberChunks.size(); i++) {
      if (memberChunks[i] & fanChunks[pos / CHUNK_SIZE + i]) {
        fail = true;
        break;
      }
    }
    if (!fail) {
      totalHugs++;
    }
  }

  return totalHugs;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    string members;
    string fans;
    cin >> members >> fans;
    cout << solve(members, fans) << '\n';
  }
  return 0;
}
