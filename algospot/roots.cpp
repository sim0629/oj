#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
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

double equals(double x0, double x1) {
  return -EPS < (x0 - x1) && (x0 - x1) < EPS;
}

double y(const vector<double> &equation, double x) {
  int degree = equation.size() - 1;
  double sum = 0;
  for (int i = 0; i <= degree; i++) {
    sum += (equation[i] * pow(x, degree - i));
  }
  return sum;
}

double search_internal(const vector<double> &equation, double x_neg, double x_pos) {
  while (!equals(x_neg, x_pos)) {
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

void print_vector(const vector<double> &v) {
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << ' ';
  }
}

void run_tests(int degree) {
  random_device rd;
  mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-10, 10);
  for (int t = 0; t < 10000; t++) {
    vector<double> answers;
    for (int i = 0; i < degree; i++) {
      answers.push_back(dis(gen));
    }
    sort(answers.begin(), answers.end());
    vector<double> equation;
    if (degree == 2) {
      equation.push_back(1);
      equation.push_back(-(answers[0] + answers[1]));
      equation.push_back(answers[0] * answers[1]);
    } else if (degree == 3) {
      equation.push_back(1);
      equation.push_back(-(answers[0] + answers[1] + answers[2]));
      equation.push_back(answers[0] * answers[1] + answers[1] * answers[2] + answers[2] * answers[0]);
      equation.push_back(-answers[0] * answers[1] * answers[2]);
    } else {
      cout << "Unsupported degree: " << degree << '\n';
      return;
    }
    cout << '[' << t << "] ";
    print_vector(equation);
    cout << '\n';
    vector<double> solutions = solve(equation);
    for (int i = 0; i < degree; i++) {
      if (!equals(answers[i], solutions[i])) {
        cout << "Found wrong answer\n";
        cout << "answers: ";
        print_vector(answers);
        cout << "\nsolutions: ";
        print_vector(solutions);
        cout << "\n";
        return;
      }
    }
  }
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
      cout.precision(10);
      cout << solutions[i];
      cout << ((i + 1 < n) ? ' ' : '\n');
    }
  }
  return 0;
}
