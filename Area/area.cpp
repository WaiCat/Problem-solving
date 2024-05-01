#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Circle {
  double x, y, r;
};

struct Point {
  double x, y;
};

bool is_inside(const Circle& c, const Point& p) {
  return sqrt(pow(p.x - c.x, 2) + pow(p.y - c.y, 2)) <= c.r;
}

Point intersect(const Circle& c1, const Circle& c2, const Circle& c3) {
  Point points;
  double d = sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
  if (d > c1.r + c2.r || d < fabs(c1.r - c2.r) || d == 0) {
    return points;
  }

  double a = (c1.r * c1.r - c2.r * c2.r + d * d) / (2 * d);
  double h = sqrt(c1.r * c1.r - a * a);
  double px = c1.x + a * (c2.x - c1.x) / d;
  double py = c1.y + a * (c2.y - c1.y) / d;

  double x1 = px + h * (c2.y - c1.y) / d;
  double y1 = py - h * (c2.x - c1.x) / d;
  double x2 = px - h * (c2.y - c1.y) / d;
  double y2 = py + h * (c2.x - c1.x) / d;

  Point p1 = {x1, y1};
  Point p2 = {x2, y2};
  if (is_inside(c3, p1)) {
    points = p1;
  }
  if ((x1 != x2 || y1 != y2) && is_inside(c3, p2)) {
    points = p2;
  }
  return points;
}

double triangle_area(const Point& p1, const Point& p2, const Point& p3) {
  return 0.5 * abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) +
                   p3.x * (p1.y - p2.y));
}

int main() {
  ifstream fin("area.inp");
  ofstream fout("area.out");

  int T;
  fin >> T;
  fout << fixed << setprecision(2);

  while (T--) {
    Circle circles[3];
    for (int i = 0; i < 3; ++i) {
      fin >> circles[i].x >> circles[i].y >> circles[i].r;
    }

    vector<Point> points;
    points.push_back(intersect(circles[0], circles[1], circles[2]));
    points.push_back(intersect(circles[1], circles[2], circles[0]));
    points.push_back(intersect(circles[2], circles[0], circles[1]));

    if (points.size() == 3) {
      double area = triangle_area(points[0], points[1], points[2]);
      fout << area << endl;
    } else {
      fout << "0.00" << endl;
    }
  }

  fin.close();
  fout.close();
  return 0;
}
