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

double distance(Point p1, Point p2) {
  return pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
}

int ccw(Point p1, Point p2, Point p3) {
  int result = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  if (result == 0) return 0;
  return (result > 0) ? 1 : -1;
}

Point findMostCounterClockwisePoint(Point& A, vector<Point>& points) {
  Point result = points[0];
  for (int i = 1; i < points.size(); i++) {
    int ccwResult = ccw(A, result, points[i]);
    if (ccwResult > 0) {
      result = points[i];
    } else if (ccwResult == 0 && distance(A, points[i]) < distance(A, result)) {
      result = points[i];
    }
  }
  return result;
}

Point findMostClockwisePoint(Point& A, vector<Point>& points) {
  if (points.empty()) return A;
  Point result = points[0];
  for (int i = 1; i < points.size(); i++) {
    int ccwResult = ccw(A, result, points[i]);
    if (ccwResult < 0) {
      result = points[i];
    } else if (ccwResult == 0 && distance(A, points[i]) < distance(A, result)) {
      result = points[i];
    }
  }
  return result;
}

double calculatePolygonArea(const std::vector<Point>& points1,
                            const std::vector<Point>& points2) {
  std::vector<Point> combinedPoints = points1;  // points1의 복사본을 만든다
  combinedPoints.insert(combinedPoints.end(), points2.begin(),
                        points2.end());  // points2의 내용을 추가한다

  int n = combinedPoints.size();
  double area = 0.0;

  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    area += combinedPoints[i].x * combinedPoints[j].y;
    area -= combinedPoints[j].x * combinedPoints[i].y;
  }

  return std::abs(area) / 2.0;
}

void addPointsBetween(vector<Point>& tangent1, vector<Point>& tangent2,
                      const vector<Point>& polygon, const Point& start,
                      const Point& end) {
  bool foundStart = false;
  int i = 0, n = polygon.size();

  // start 위치 찾기
  for (i = 0; i < n; ++i) {
    if (polygon[i].x == start.x && polygon[i].y == start.y) {
      foundStart = true;
      break;
    }
  }

  // start에서 end까지의 점들을 tangent1에 추가
  if (foundStart) {
    while (true) {
      tangent1.push_back(polygon[i]);  // 현재 점 추가
      if (polygon[i].x == end.x && polygon[i].y == end.y) {
        break;  // end에 도달하면 종료
      }
      i = (i + 1) % n;  // 순환적으로 다음 인덱스로 이동
    }
  }

  // end에서 start까지의 점들을 tangent2에 추가
  foundStart = false;
  for (i = 0; i < n; ++i) {
    if (polygon[i].x == end.x && polygon[i].y == end.y) {
      foundStart = true;
      break;
    }
  }
  if (foundStart) {
    while (true) {
      tangent2.push_back(polygon[i]);  // 현재 점 추가
      if (polygon[i].x == start.x && polygon[i].y == start.y) {
        break;  // start에 도달하면 종료
      }
      i = (i + 1) % n;  // 순환적으로 다음 인덱스로 이동
    }
  }
}

int main() {
  ifstream fin("3.inp");
  ofstream fout("3.txt");

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
    p1 = findMostCounterClockwisePoint(p2, polygon2);

    p3 = findMostClockwisePoint(polygon1[0], polygon2);
    p4 = findMostCounterClockwisePoint(p3, polygon1);
    p3 = findMostClockwisePoint(p4, polygon2);

    cout << "p1: (" << p1.x << ", " << p1.y << ")\n";
    cout << "p3: (" << p3.x << ", " << p3.y << ")\n";
    cout << "p2: (" << p2.x << ", " << p2.y << ")\n";
    cout << "p4: (" << p4.x << ", " << p4.y << ")\n";
    cout << endl;

    vector<Point> tangent1, tangent2, tangent3, tangent4;
    addPointsBetween(tangent1, tangent2, polygon1, p2, p4);
    addPointsBetween(tangent3, tangent4, polygon2, p1, p3);

    cout << "Tangent1 points:\n";
    for (const Point& pt : tangent1) {
      cout << "(" << pt.x << ", " << pt.y << ")\n";
    }

    cout << "Tangent2 points:\n";
    for (const Point& pt : tangent2) {
      cout << "(" << pt.x << ", " << pt.y << ")\n";
    }

    cout << "Tangent3 points:\n";
    for (const Point& pt : tangent3) {
      cout << "(" << pt.x << ", " << pt.y << ")\n";
    }

    cout << "Tangent4 points:\n";
    for (const Point& pt : tangent4) {
      cout << "(" << pt.x << ", " << pt.y << ")\n";
    }

    // vector<Point> tangent1, tangent2, tangent3, tangent4;
    // bool change = true;
    // Point p;
    // bool first = false;
    // bool second = false;

    // for (int i = 0; i < polygon1.size(); i++) {
    //   if (polygon1[i].x == p2.x && polygon1[i].y == p2.y) {
    //     tangent1.push_back(polygon1[i]);
    //     tangent2.push_back(polygon1[i]);
    //     change = !change;
    //     first = false;
    //     continue;
    //   }
    //   if (polygon1[i].x == p4.x && polygon1[i].y == p4.y) {
    //     tangent1.push_back(polygon1[i]);
    //     tangent2.push_back(polygon1[i]);
    //     change = !change;
    //     first = true;
    //     continue;
    //   }
    //   if (change) {
    //     tangent1.push_back(polygon1[i]);
    //   } else {
    //     tangent2.push_back(polygon1[i]);
    //   }
    // }

    // for (int i = 0; i < polygon2.size(); i++) {
    //   if (polygon2[i].x == p1.x && polygon2[i].y == p1.y) {
    //     tangent3.push_back(polygon2[i]);
    //     tangent4.push_back(polygon2[i]);
    //     change = !change;
    //     second = false;
    //     continue;
    //   }
    //   if (polygon2[i].x == p3.x && polygon2[i].y == p3.y) {
    //     tangent3.push_back(polygon2[i]);
    //     tangent4.push_back(polygon2[i]);
    //     change = !change;
    //     second = true;
    //     continue;
    //   }
    //   if (change) {
    //     tangent3.push_back(polygon2[i]);
    //   } else {
    //     tangent4.push_back(polygon2[i]);
    //   }
    // }
    // double area1, area2;
    // if (first && second) {
    //   area1 = calculatePolygonArea(tangent1, tangent4);
    //   area2 = calculatePolygonArea(tangent2, tangent3);
    // } else {
    //   area1 = calculatePolygonArea(tangent2, tangent4);
    //   area2 = calculatePolygonArea(tangent1, tangent3);
    // }

    double area1, area2;

    area1 = calculatePolygonArea(tangent1, tangent4);
    area2 = calculatePolygonArea(tangent2, tangent3);
    // area1 = calculatePolygonArea(tangent2, tangent4);
    // area2 = calculatePolygonArea(tangent1, tangent3);
    fout << fixed << setprecision(1);  // 소수점 한 자리까지 고정하여 출력
    fout << min(area1, area2) << endl;
  }

  return 0;
}
