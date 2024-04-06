#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Point {
 public:
  int x, y;
};

double distance(Point p1, Point p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int ccw(Point p1, Point p2, Point p3) {
  int result = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  if (result == 0) return 0;
  return (result > 0) ? 1 : -1;
}

vector<Point> convexHull(vector<Point>& points) {
  int n = points.size();
  if (n <= 3) return points;

  int min_idx = 0;
  for (int i = 1; i < n; i++) {
    if (points[i].x < points[min_idx].x ||
        (points[i].x == points[min_idx].x && points[i].y < points[min_idx].y))
      min_idx = i;
  }
  swap(points[0], points[min_idx]);

  sort(points.begin() + 1, points.end(), [&](Point p1, Point p2) {
    int val = ccw(points[0], p1, p2);
    if (val == 0) return distance(points[0], p1) < distance(points[0], p2);
    return val > 0;
  });

  stack<Point> hull;
  hull.push(points[0]);
  hull.push(points[1]);
  for (int i = 2; i < n; i++) {
    while (hull.size() >= 2) {
      Point p1 = hull.top();
      hull.pop();
      Point p2 = hull.top();
      if (ccw(p2, p1, points[i]) > 0) {
        hull.push(p1);
        break;
      }
    }
    hull.push(points[i]);
  }

  vector<Point> result;
  while (!hull.empty()) {
    result.push_back(hull.top());
    hull.pop();
  }
  reverse(result.begin(), result.end());
  return result;
}

int main() {
  ifstream fin("hull.inp");
  ofstream fout("hull.out");

  int n;
  fin >> n;

  vector<Point> points;

  for (int i = 0; i < n; i++) {
    Point p;
    fin >> p.x >> p.y;
    points.push_back(p);
  }

  vector<Point> convex_hull = convexHull(points);
  fout << convex_hull.size() << endl;
  for (Point p : convex_hull) {
    fout << p.x << " " << p.y << endl;
  }
  return 0;
}
