#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void findRightTriangles(int n, vector<int>& length) {
  set<double> ratios;
  for (int a = 1; a <= n; ++a) {
    for (int b = a; b <= n; ++b) {
      int c = sqrt(a * a + b * b);
      if (c * c == a * a + b * b && a + b + c <= n) {
        double ratio = static_cast<double>(a) / b;
        bool isMultiple = false;
        for (double r : ratios) {
          if (fmod(ratio, r) == 0 || fmod(r, ratio) == 0) {
            isMultiple = true;
            break;
          }
        }
        if (isMultiple) {
          continue;
        }
        ratios.insert(ratio);
        length.push_back((a + b) * 2);
      }
    }
  }
}

int main() {
  ifstream fin("rectangles.inp");
  ofstream fout("rectangles.out");

  int n = 10000;
  vector<int> length;

  int t;
  fin >> t;
  findRightTriangles(n, length);
  sort(length.begin(), length.end());
  for (int i = 0; i < t; i++) {
    int L, count = 0;
    fin >> L;

    for (int k : length) {
      L -= k;
      if (L < 0) {
        break;
      }
      count++;
    }
    fout << count << endl;
  }

  return 0;
}
