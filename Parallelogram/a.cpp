#include <math.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <stack>
#include <vector>

using namespace std;

struct Point {
  long long x, y;
};
Point a, b, c, d;

double getInclination(Point a, Point b) {
  long long tmp = abs(a.x - b.x);
  if (tmp == 0) {
    return INFINITY;
  }
  // return abs(a.y - b.y) / abs(a.x - b.x);
  return abs(a.y - b.y) / static_cast<double>(abs(a.x - b.x));
}

double getLength(Point a, Point b) {
  long long x = a.x - b.x;
  long long y = a.y - b.y;
  return sqrt(x * x + y * y);
}

int main() {
  ifstream fin;
  ofstream fout;
  fin.open("0.inp");
  fout.open("0.txt");

  while (true) {
    fin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
    if (a.x == 0 && a.y == 0 && b.x == 0 && b.y == 0 && c.x == 0 && c.y == 0 &&
        d.x == 0 && d.y == 0)
      break;

    // a,b �Ÿ�
    double ablen = getLength(a, b);
    double cdlen = getLength(c, d);
    if (ablen == cdlen) {
      double abr = getInclination(a, b);
      double cdr = getInclination(c, d);
      if (abr == cdr) fout << 1 << endl;
      continue;
    }

    double aclen = getLength(a, c);
    double bdlen = getLength(b, d);
    if (aclen == bdlen) {
      double acr = getInclination(a, c);
      double bdr = getInclination(b, d);
      if (acr == bdr) fout << 1 << endl;
      continue;
    }
    fout << 0 << endl;
  }
}