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

bool isLine(int a, int b, int c, int d)
{
    if (a > b) // b가 더 크게
    {
        swap(a, b);
    }
    if (c > d) // d가 더 크게
    {
        swap(c, d);
    }
    return (a <= d && b >= c) || (c <= b && d >= a); // 좌표의 대소 관계 확인
}
bool isCross(Point p1, Point p2, Point p3, Point p4)
{
    // ccw 구하기
    int z1 = ccw(p1, p2, p3);
    int z2 = ccw(p1, p2, p4);
    int z3 = ccw(p3, p4, p1);
    int z4 = ccw(p3, p4, p2);

    if (z1 * z2 == 0 && z3 * z4 == 0) // 같은 선상에 있는 경우
    {
        return isLine(p1.x, p2.x, p3.x, p4.x) && isLine(p1.y, p2.y, p3.y, p4.y);
    }

    return z1 * z2 <= 0 && z3 * z4 <= 0;
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
  ifstream fin("1.inp");
  ofstream fout("1.txt");

  int t;
  fin >> t;

  for (size_t j = 0; j < t; j++)
  {
    int n;
    fin >> n;

    vector<Point> points;

    for (int i = 0; i < 4; i++) {
      Point p;
      fin >> p.x >> p.y;
      points.push_back(p);
    }


    if(isCross(points[0], points[1], points[2], points[3]) || isCross( points[0],  points[3],  points[1],  points[2])){
        fout << 1;
      }
    else{
      vector<Point> convex_hull = convexHull(points);
      if(convex_hull.size()<4){
          fout << 2;
      }else{
          fout << 3;
      }
    }
    fout << endl;

  }

  


  return 0;
}
