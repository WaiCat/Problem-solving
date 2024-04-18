#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Point {
 public:
  int x, y;
  bool number;
};

double distance(Point p1, Point p2) {
  return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
}

int ccw(Point p1, Point p2, Point p3) {
  int result = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  if (result == 0) return 0;
  return (result > 0) ? 1 : -1;
}

void convexHull(vector<Point>& Points, vector<Point>& contact1,
                vector<Point>& contact2) {
  int n = Points.size();

  int min_idx = 0;
  for (int i = 1; i < n; i++) {
    if (Points[i].x < Points[min_idx].x ||
        (Points[i].x == Points[min_idx].x && Points[i].y < Points[min_idx].y))
      min_idx = i;
  }
  swap(Points[0], Points[min_idx]);

  sort(Points.begin() + 1, Points.end(), [&](Point p1, Point p2) {
    int val = ccw(Points[0], p1, p2);
    if (val == 0) return distance(Points[0], p1) < distance(Points[0], p2);
    return val > 0;
  });

  stack<Point> hull;
  hull.push(Points[0]);
  hull.push(Points[1]);
  for (int i = 2; i < n; i++) {
    while (hull.size() >= 2) {
      Point p1 = hull.top();
      hull.pop();
      Point p2 = hull.top();
      if (ccw(p2, p1, Points[i]) > 0) {
        hull.push(p1);
        break;
      }
    }
    hull.push(Points[i]);
  }

  vector<Point> result;
  while (!hull.empty()) {
    result.push_back(hull.top());
    hull.pop();
  }
  reverse(result.begin(), result.end());

  int size = result.size();
  for (int i = 0; i < size; ++i) {
    int j = (i + 1) % size;
    if (result[i].number != result[j].number) {
      if (result[i].number)
        contact2.push_back(result[i]), contact1.push_back(result[j]);
      else
        contact1.push_back(result[i]), contact2.push_back(result[j]);
    }
  }
}

int isBetween(Point a, Point b, Point c) {
  if (ccw(a, b, c)) {
    return 0;
  }
  if (a.x != b.x) {
    if (b.x < a.x) {
      return a.x >= c.x && c.x >= b.x ? 1 : 0;
    } else {
      return a.x <= c.x && c.x <= b.x ? 1 : 0;
      ;
    }
  } else {
    if (b.y < a.y) {
      return a.y >= c.y && c.y >= b.y ? 1 : 0;
      ;
    } else {
      return a.y <= c.y && c.y <= b.y ? 1 : 0;
      ;
    }
  }
}

Point findMostCounterClockwisePoint(Point& A, vector<Point>& Points) {
  Point result = Points[0];
  for (int i = 1; i < Points.size(); i++) {
    int ccwResult = ccw(A, result, Points[i]);
    if (ccwResult > 0) {
      result = Points[i];
    } else if (ccwResult == 0 && distance(A, Points[i]) < distance(A, result)) {
      result = Points[i];
    }
  }
  return result;
}

Point findMostClockwisePoint(Point& A, vector<Point>& Points) {
  if (Points.empty()) return A;
  Point result = Points[0];
  for (int i = 1; i < Points.size(); i++) {
    int ccwResult = ccw(A, result, Points[i]);
    if (ccwResult < 0) {
      result = Points[i];
    } else if (ccwResult == 0 && distance(A, Points[i]) < distance(A, result)) {
      result = Points[i];
    }
  }
  return result;
}

double calculatePolygonArea(const vector<Point>& Points) {
  int n = Points.size();
  double area = 0.0;

  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    area += Points[i].x * Points[j].y;
    area -= Points[j].x * Points[i].y;
  }

  return abs(area) / 2.0;
}

int main() {
  ifstream fin("tangent.inp");
  ofstream fout("tangent.out");

  int t;
  fin >> t;

  for (int k = 0; k < t; k++) {
    vector<Point> polygon, polygon1, polygon2, hull;

    int n, m;

    fin >> n;
    for (int i = 0; i < n; i++) {
      Point p;
      fin >> p.x >> p.y;
      polygon1.push_back(p);
      p.number = false;
      polygon.push_back(p);
    }
    fin >> m;
    for (int i = 0; i < m; i++) {
      Point p;
      fin >> p.x >> p.y;
      polygon2.push_back(p);
      p.number = true;
      polygon.push_back(p);
    }

    Point p1, p2, p3, p4;

    vector<Point> contact1, contact2;
    convexHull(polygon, contact1, contact2);

    for (int i = 0; i < n + m; ++i) {
      if (polygon[i].number) {
        if (isBetween(contact1[0], contact2[0], polygon[i]))
          contact2[0] = polygon[i];
      } else {
        if (isBetween(contact1[0], contact2[0], polygon[i]))
          contact1[0] = polygon[i];
      }
    }
    for (int i = 0; i < n + m; ++i) {
      if (polygon[i].number) {
        if (isBetween(contact1[1], contact2[1], polygon[i]))
          contact2[1] = polygon[i];
      } else {
        if (isBetween(contact1[1], contact2[1], polygon[i]))
          contact1[1] = polygon[i];
      }
    }

    p1 = contact2[0];
    p2 = contact1[0];
    p3 = contact2[1];
    p4 = contact1[1];

    vector<Point> tangent1, tangent2;
    Point p;

    int start, i;

    int size = polygon1.size();
    for (i = 0; i < size; i++) {
      if (polygon1[i].x == p2.x && polygon1[i].y == p2.y) {
        start = i;
        while (true) {
          tangent1.push_back(polygon1[i]);
          i = (i + 1) % size;
          if (polygon1[i].x == p4.x && polygon1[i].y == p4.y) {
            tangent1.push_back(polygon1[i]);
            break;
          }
        }
        break;
      }
    }

    while (true) {
      tangent2.push_back(polygon1[i]);
      i = (i + 1) % size;
      if (i == start) {
        tangent2.push_back(polygon1[i]);
        break;
      }
    }

    size = polygon2.size();
    for (i = 0; i < size; i++) {
      if (polygon2[i].x == p3.x && polygon2[i].y == p3.y) {
        start = i;
        while (true) {
          tangent1.push_back(polygon2[i]);
          i = (i + 1) % size;
          if (polygon2[i].x == p1.x && polygon2[i].y == p1.y) {
            tangent1.push_back(polygon2[i]);
            break;
          }
        }
        break;
      }
    }

    while (true) {
      tangent2.push_back(polygon2[i]);
      i = (i + 1) % size;
      if (i == start) {
        tangent2.push_back(polygon2[i]);
        break;
      }
    }

    double area1 = calculatePolygonArea(tangent1);
    double area2 = calculatePolygonArea(tangent2);

    fout << fixed << setprecision(1);  // 소수점 한 자리까지 고정하여 출력
    fout << min(area1, area2) << endl;
  }

  return 0;
}