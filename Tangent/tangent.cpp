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
};

int ccw(Point p1, Point p2, Point p3) {
  int result = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  if (result == 0) return 0;
  return (result > 0) ? 1 : -1;
}

Point findMostCounterClockwisePoint(Point& A, vector<Point>& points) {
  Point mostCCW = points[0];
  for (int i = 1; i < points.size(); i++) {
    if (ccw(A, mostCCW, points[i]) > 0) {
      mostCCW = points[i];
    }
  }
  return mostCCW;
}

Point findMostClockwisePoint(Point& A, vector<Point>& points) {
  if (points.size() < 1) return A;
  Point mostCW = points[0];
  for (int i = 1; i < points.size(); i++) {
    if (ccw(A, mostCW, points[i]) < 0) {
      mostCW = points[i];
    }
  }
  return mostCW;
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

vector<Point> readPolygon(ifstream& fin) {
  int n;
  fin >> n;
  vector<Point> polygon(n);
  for (int i = 0; i < n; ++i) {
    fin >> polygon[i].x >> polygon[i].y;
  }
  return polygon;
}

void findAndPrintTangentPoints(vector<Point>& polygon1, vector<Point>& polygon2,
                               ofstream& fout) {
  Point tangentStart = findMostCounterClockwisePoint(polygon1[0], polygon2);
  Point tangentEnd = findMostClockwisePoint(tangentStart, polygon1);

  // 이 과정을 반복하여 탄젠트 포인트를 찾습니다.
  Point tempStart, tempEnd;
  do {
    tempStart = tangentStart;
    tempEnd = tangentEnd;
    tangentStart = findMostCounterClockwisePoint(tangentEnd, polygon2);
    tangentEnd = findMostClockwisePoint(tangentStart, polygon1);
  } while (tempStart.x != tangentStart.x || tempStart.y != tangentStart.y ||
           tempEnd.x != tangentEnd.x || tempEnd.y != tangentEnd.y);

  fout << tangentStart.x << ", " << tangentStart.y << endl;
  fout << tangentEnd.x << ", " << tangentEnd.y << endl;
}

int main() {
  ifstream fin("1.inp");
  ofstream fout("1.txt");

  int t;
  fin >> t;

  for (int k = 0; k < t; k++) {
    vector<Point> polygon1, polygon2;

    int n;

    fin >> n;
    for (int i = 0; i < n; i++) {
      Point p;
      fin >> p.x >> p.y;
      polygon1.push_back(p);
    }
    fin >> n;
    for (int i = 0; i < n; i++) {
      Point p;
      fin >> p.x >> p.y;
      polygon2.push_back(p);
    }

    Point p1, p2, p3, p4;

    p1 = findMostCounterClockwisePoint(polygon1[0], polygon2);  // polygon2의점
    p2 = findMostClockwisePoint(p1, polygon1);  // polygon1의점

    while (true) {
      Point p1t = p1, p2t = p2;
      p1 = findMostCounterClockwisePoint(p2, polygon2);
      p2 = findMostClockwisePoint(p1, polygon1);
      if (p1t.x == p1.x && p1t.y == p1.y && p2t.x == p2.x && p2t.y == p2.y) {
        break;
      }
    }

    cout << p1.x << ", " << p1.y << endl;
    cout << p2.x << ", " << p2.y << endl;

    p3 = findMostClockwisePoint(polygon1[0], polygon2);  // polygon2의점
    p4 = findMostCounterClockwisePoint(p3, polygon1);    // polygon1의점

    while (true) {
      Point p1t = p3, p2t = p4;
      p3 = findMostClockwisePoint(p4, polygon2);
      p4 = findMostCounterClockwisePoint(p3, polygon1);
      if (p1t.x == p3.x && p1t.y == p3.y && p2t.x == p4.x && p2t.y == p4.y) {
        break;
      }
    }

    cout << p3.x << ", " << p3.y << endl;
    cout << p4.x << ", " << p4.y << endl;

    vector<Point> tangent1, tangent2;
    bool search = false;
    Point p;
    for (int i = 0; i < polygon1.size(); i++) {
      if (polygon1[i].x == p2.x && polygon1[i].y == p2.y) {
        search = true;
      }
      if (search) {
        while (search) {
          tangent1.push_back(polygon1[i]);
          i++;
          if (i == polygon1.size()) {
            i = 0;
          }
          if (polygon1[i].x == p4.x && polygon1[i].y == p4.y) {
            tangent1.push_back(polygon1[i]);
            break;
          }
        }
        break;
      }
    }

    search = false;
    for (int i = 0; i < polygon2.size(); i++) {
      if (polygon2[i].x == p3.x && polygon2[i].y == p3.y) {
        search = true;
      }
      if (search) {
        while (search) {
          tangent1.push_back(polygon2[i]);
          i++;
          if (i == polygon2.size()) {
            i = 0;
          }
          if (polygon2[i].x == p1.x && polygon2[i].y == p1.y) {
            tangent1.push_back(polygon2[i]);
            break;
          }
        }
        break;
      }
    }

    search = false;
    for (int i = 0; i < polygon1.size(); i++) {
      if (polygon1[i].x == p4.x && polygon1[i].y == p4.y) {
        search = true;
      }
      if (search) {
        while (search) {
          tangent2.push_back(polygon1[i]);
          i++;
          if (i == polygon1.size()) {
            i = 0;
          }
          if (polygon1[i].x == p2.x && polygon1[i].y == p2.y) {
            tangent2.push_back(polygon1[i]);
            break;
          }
        }
        break;
      }
    }

    search = false;
    for (int i = 0; i < polygon2.size(); i++) {
      if (polygon2[i].x == p1.x && polygon2[i].y == p1.y) {
        search = true;
      }
      if (search) {
        while (search) {
          tangent2.push_back(polygon2[i]);
          i++;
          if (i == polygon2.size()) {
            i = 0;
          }
          if (polygon2[i].x == p3.x && polygon2[i].y == p3.y) {
            tangent2.push_back(polygon2[i]);
            break;
          }
        }
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
