#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

struct Point {
  double x, y;
};

// 두 점 사이의 거리를 계산하는 함수
double distance(Point p1, Point p2) {
  return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

// 두 점을 이용하여 직선의 기울기를 계산하는 함수
double calculateSlope(Point p1, Point p2) {
  // 분모가 0이 되는 경우 처리
  if (p2.x - p1.x == 0) {
    // 무한대 기울기
    return INFINITY;
  }
  return (p2.y - p1.y) / (p2.x - p1.x);
}

// 두 직선이 평행한지 확인하는 함수
bool areParallel(Point p1, Point p2, Point p3, Point p4) {
  double slope1 = calculateSlope(p1, p2);
  double slope2 = calculateSlope(p3, p4);

  // 두 직선의 기울기가 같으면 평행한 직선이다
  return (slope1 == slope2);
}

// 주어진 네 점이 평행사변형인지 확인하는 함수
bool isParallelogram(Point p1, Point p2, Point p3, Point p4) {
  double d1, d2, d3, d4;

  // 각 변의 길이 계산
  d1 = distance(p1, p2);
  d2 = distance(p2, p3);
  d3 = distance(p3, p4);
  d4 = distance(p4, p1);

  // 대응하는 변의 길이가 서로 같아야 함
  if (abs(d1 - d3) > 0.0001 || abs(d2 - d4) > 0.0001) return false;

  // 대각선이 서로 평행해야 함
  if (!areParallel(p1, p2, p3, p4) && !areParallel(p1, p3, p2, p4))
    return false;

  return true;
}

int main() {
  ifstream fin("2.inp");
  ofstream fout("2.txt");

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
