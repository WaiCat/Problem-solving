#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
  int x, y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

double crossProduct(const Point& O, const Point& A, const Point& B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

double calculatePolygonArea(const vector<Point>& points) {
  int n = points.size();
  double area = 0.0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    area += points[i].x * points[j].y;
    area -= points[j].x * points[i].y;
  }
  return abs(area) / 2.0;
}

vector<Point> extractPolygonSection(const vector<Point>& polygon, Point start,
                                    Point end) {
  vector<Point> section;
  bool collecting = false;
  int n = polygon.size();

  for (int i = 0; i < n; i++) {
    if (polygon[i] == start) collecting = true;
    if (collecting) section.push_back(polygon[i]);
    if (polygon[i] == end) break;
  }
  return section;
}

void findTangentPoints(const vector<Point>& poly1, const vector<Point>& poly2,
                       Point& tangentStart, Point& tangentEnd) {
  double maxDist = -1.0;
  for (const auto& p1 : poly1) {
    for (const auto& p2 : poly2) {
      double dist =
          crossProduct(p1, p2, p2);  // Just use squared distance for comparison
      if (dist > maxDist) {
        maxDist = dist;
        tangentStart = p1;
        tangentEnd = p2;
      }
    }
  }
}

int main() {
  ifstream fin("3.inp");
  ofstream fout("3.txt");

  int t;
  fin >> t;
  fout << fixed << setprecision(1);

  while (t--) {
    int n, m;
    vector<Point> polygon1, polygon2;

    fin >> n;
    for (int i = 0; i < n; i++) {
      Point p;
      fin >> p.x >> p.y;
      polygon1.push_back(p);
    }

    fin >> m;
    for (int i = 0; i < m; i++) {
      Point p;
      fin >> p.x >> p.y;
      polygon2.push_back(p);
    }

    Point p1, p2, p3, p4;
    findTangentPoints(polygon1, polygon2, p1, p2);
    findTangentPoints(polygon2, polygon1, p3, p4);

    cout << "p1: (" << p1.x << ", " << p1.y << ")\n";
    cout << "p2: (" << p2.x << ", " << p2.y << ")\n";
    cout << "p3: (" << p3.x << ", " << p3.y << ")\n";
    cout << "p4: (" << p4.x << ", " << p4.y << ")\n";
    cout << endl;

    vector<Point> areaPolygon = extractPolygonSection(polygon1, p1, p3);
    vector<Point> temp = extractPolygonSection(polygon2, p2, p4);
    areaPolygon.insert(areaPolygon.end(), temp.begin(), temp.end());

    double area = calculatePolygonArea(areaPolygon);
    fout << area << endl;
  }

  return 0;
}
