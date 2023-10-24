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

const double EPS = 1e-10;
const double ROOT_MIN = -11;
const double ROOT_MAX = 11;

double y(const vector<double> &equation, double x) {
  int degree = equation.size() - 1;
  double sum = 0;
  for (int i = 0; i <= degree; i++) {
    sum += (equation[i] * pow(x, degree - i));
  }
  return sum;
}

double search_internal(const vector<double> &equation, double x_neg, double x_pos) {
  while (!(-EPS < (x_neg - x_pos) && (x_neg - x_pos) < EPS)) {
    double x_new = (x_neg + x_pos) / 2;
    double y_new = y(equation, x_new);
    if (y_new > 0) {
      x_pos = x_new;
    } else {
      x_neg = x_new;
    }
  }
  return x_pos;
}

double search(const vector<double> &equation, double x_left, double x_right) {
  double y_left = y(equation, x_left);
  if (y_left < 0) {
    return search_internal(equation, x_left, x_right);
  } else {
    return search_internal(equation, x_right, x_left);
  }
}

vector<double> solve(const vector<double> &equation) {
  int degree = equation.size() - 1;
  vector<double> solutions;

  if (degree == 1) {
    solutions.push_back(-equation[1] / equation[0]);
    return solutions;
  }

  vector<double> derivative;
  for (int i = 0; i < degree; i++) {
    derivative.push_back((degree - i) * equation[i]);
  }

  vector<double> inflections = solve(derivative);
  solutions.push_back(search(equation, ROOT_MIN, inflections[0]));
  for (int i = 1; i < inflections.size(); i++) {
    solutions.push_back(search(equation, inflections[i - 1], inflections[i]));
  }
  solutions.push_back(search(equation, inflections[inflections.size() - 1], ROOT_MAX));
  return solutions;
}

int main(void) {
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int C;
  cin >> C;
  while (C--) {
    int n;
    cin >> n;
    vector<double> equation;
    for (int i = 0; i < n + 1; i++) {
      double coeff;
      cin >> coeff;
      equation.push_back(coeff);
    }
    vector<double> solutions = solve(equation);
    for (int i = 0; i < n; i++) {
      cout << solutions[i];
      cout << ((i + 1 < n) ? ' ' : '\n');
    }
  }
  return 0;
}
