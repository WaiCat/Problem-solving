#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

struct Point {
  double x, y;
};

double distance(Point p1, Point p2) {
  return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double calculateSlope(Point p1, Point p2) {
  if (p2.x - p1.x == 0) {
    return INFINITY;
  }
  return (p2.y - p1.y) / (p2.x - p1.x);
}

bool areParallel(Point p1, Point p2, Point p3, Point p4) {
  double slope1 = calculateSlope(p1, p2);
  double slope2 = calculateSlope(p3, p4);

  return (slope1 == slope2);
}

bool isParallelogram(Point p1, Point p2, Point p3, Point p4) {
  double d1, d2;

  d1 = distance(p1, p2);
  d2 = distance(p3, p4);

  if (d1 != d2) return false;

  if (!areParallel(p1, p2, p3, p4)) return false;

  return true;
}

int main() {
  ifstream fin("parallelogram.inp");
  ofstream fout("parallelogram.out");

  Point points[4];

  while (true) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
      fin >> points[i].x >> points[i].y;
      if (points[i].x == 0 && points[i].y == 0) {
        count++;
      }
    }
    if (count == 4) {
      break;
    }

    if (isParallelogram(points[0], points[1], points[2], points[3])) {
      fout << "1" << endl;
    } else if (isParallelogram(points[0], points[2], points[1], points[3])) {
      fout << "1" << endl;
    } else {
      fout << "0" << endl;
    }
  }

  fin.close();
  fout.close();

  return 0;
}
