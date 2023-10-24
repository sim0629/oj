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

double newton(const vector<double> &equation, const vector<double> &derivative, double x0) {
  double y0, y1, x1, x_diff;
  while (true) {
    y0 = y(equation, x0);
    y1 = y(derivative, x0);
    x1 = x0 - y0 / y1;
    x_diff = x1 - x0;
    if (-EPS < x_diff && x_diff < EPS) {
      return x1;
    }
    x0 = x1;
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
  solutions.push_back(newton(equation, derivative, (ROOT_MIN + inflections[0]) / 2));
  for (int i = 1; i < inflections.size(); i++) {
    solutions.push_back(newton(equation, derivative, (inflections[i - 1] + inflections[i]) / 2));
  }
  solutions.push_back(newton(equation, derivative, (inflections[inflections.size() - 1] + ROOT_MAX) / 2));
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
