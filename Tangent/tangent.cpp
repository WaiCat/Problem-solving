#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
  double x, y;
  Point(double _x, double _y) : x(_x), y(_y) {}
};

struct Line {
  double a, b, c;  // ax + by = c
  Line(Point p1, Point p2) {
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = a * p1.x + b * p1.y;
  }
};

Point findIntersection(Line l1, Line l2) {
  double determinant = l1.a * l2.b - l2.a * l1.b;
  double x = (l2.b * l1.c - l1.b * l2.c) / determinant;
  double y = (l1.a * l2.c - l2.a * l1.c) / determinant;
  return Point(x, y);
}

void findTangent(Point p, const vector<Point>& polygon,
                 vector<Point>& tangents) {
  int n = polygon.size();
  for (int i = 0; i < n; ++i) {
    Point p1 = polygon[i];
    Point p2 = polygon[(i + 1) % n];
    Line line(p, Point(p.x + (p.y - p1.y),
                       p.y - (p.x - p1.x)));  // perpendicular line through p
    Line side(p1, p2);
    Point intersection = findIntersection(line, side);
    // Check if the intersection point lies outside the polygon
    bool outside = true;
    for (int j = 0; j < n; ++j) {
      if ((polygon[j].x - p.x) * (intersection.y - p.y) -
              (polygon[j].y - p.y) * (intersection.x - p.x) >
          0) {
        outside = false;
        break;
      }
    }
    if (outside) {
      tangents.push_back(intersection);
    }
  }
}

int main() {
  // Define polygons (as vectors of points)
  vector<Point> polygon1 = {{12, 12}, {12, 23}, {5, 7},
                            {6, 8},   {10, -3}, {22, 5}};  // Example polygon 1
  vector<Point> polygon2 = {
      {26, 10}, {29, -4}, {28, 16}, {32, 25}, {25, 20}};  // Example polygon 2

  // Find tangents
  vector<pair<Point, Point>> tangents;
  for (const Point& p1 : polygon1) {
    vector<Point> tangentsFromP1;
    findTangent(p1, polygon2, tangentsFromP1);
    for (const Point& p2 : tangentsFromP1) {
      tangents.push_back({p1, p2});
    }
  }

  // Print results
  cout << "Tangent points:" << endl;
  for (const auto& tangent : tangents) {
    cout << "Point on polygon 1: (" << tangent.first.x << ", "
         << tangent.first.y << ")";
    cout << ", Point on polygon 2: (" << tangent.second.x << ", "
         << tangent.second.y << ")" << endl;
  }

  return 0;
}
