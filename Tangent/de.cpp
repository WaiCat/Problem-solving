#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#pragma warning(disable : 4996)
#define MAX_N 10001
using namespace std;
typedef long long int llt;
class point {
 public:
  llt x, y, dx, dy;
  int idx;
  bool ab;
  point(llt x = 0, llt y = 0, bool ab = false)
      : x(x), y(y), ab(ab), dx(0), dy(0), idx(0) {}
  bool operator<(const point& p) const {
    if (dy * p.dx != dx * p.dy) return dy * p.dx < dx * p.dy;
    return x == p.x ? y < p.y : x < p.x;
  }
  bool operator==(const point& p) const { return x == p.x && y == p.y; }
};
int t, n, m;
point pos[MAX_N + MAX_N], Apos[MAX_N], Bpos[MAX_N];
vector<point> convex, ap, bp, hull;

llt ccw(point& a, point& b, point& c) {
  return a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x;
}

void swap_point(point& p1, point& p2) {
  point tmp = p1;
  p1 = p2;
  p2 = tmp;
}

void make_hull(int sz, point pos[], vector<point>& v, bool flag) {
  if (flag) {
    for (int i = v[1].idx;; i = (i + 1) % sz) {
      hull.push_back(pos[i]);
      if (pos[i] == v[0]) return;
    }
  } else {
    for (int i = v[0].idx;; i = (i + 1) % sz) {
      hull.push_back(pos[i]);
      if (pos[i] == v[1]) return;
    }
  }
}

bool between(point a, point b, point c) {
  if (ccw(a, b, c)) return 0;
  if (a.x != b.x) {
    if (b.x < a.x) swap_point(a, b);
    return a.x <= c.x && c.x <= b.x;
  } else {
    if (b.y < a.y) swap_point(a, b);
    return a.y <= c.y && c.y <= b.y;
  }
}

int main() {
  ifstream fin("3.inp");
  ofstream fout("3.txt");

  fin >> t;
  while (t--) {
    fin >> n;
    for (int i = 0; i < n; ++i) {
      fin >> Apos[i].x >> Apos[i].y;
      Apos[i].idx = i;
      pos[i].x = Apos[i].x, pos[i].y = Apos[i].y;
      pos[i].idx = i;
    }
    fin >> m;
    for (int i = 0; i < m; ++i) {
      fin >> Bpos[i].x >> Bpos[i].y;
      Bpos[i].idx = i;
      pos[i + n].x = Bpos[i].x, pos[i + n].y = Bpos[i].y;
      pos[i + n].ab = 1;
      pos[i + n].idx = i;
    }
    for (int i = 1; i < n + m; ++i) {
      if (pos[i] < pos[0]) swap(pos[i], pos[0]);
    }
    for (int i = 1; i < n + m; ++i)
      pos[i].dx = pos[i].x - pos[0].x, pos[i].dy = pos[i].y - pos[0].y;
    sort(pos + 1, pos + n + m);
    for (int i = 0; i < n + m; ++i) {
      while (convex.size() > 1 &&
             ccw(convex[convex.size() - 2], convex.back(), pos[i]) <= 0)
        convex.pop_back();
      convex.push_back(pos[i]);
    }
    int sz = convex.size();
    for (int i = 0; i < sz; ++i) {
      int j = (i + 1) % sz;
      if (convex[i].ab != convex[j].ab) {
        if (convex[i].ab)
          bp.push_back(convex[i]), ap.push_back(convex[j]);
        else
          ap.push_back(convex[i]), bp.push_back(convex[j]);
      }
    }
    for (int i = 0; i < n + m; ++i) {
      if (pos[i].ab) {
        if (between(ap[0], bp[0], pos[i])) bp[0] = pos[i];
      } else {
        if (between(ap[0], bp[0], pos[i])) ap[0] = pos[i];
      }
    }
    for (int i = 0; i < n + m; ++i) {
      if (pos[i].ab) {
        if (between(ap[1], bp[1], pos[i])) bp[1] = pos[i];
      } else {
        if (between(ap[1], bp[1], pos[i])) ap[1] = pos[i];
      }
    }
    bool flag = 0;
    if (bp[0] < ap[0]) flag = !flag;
    if (!flag) {
      make_hull(n, Apos, ap, flag);
      make_hull(m, Bpos, bp, !flag);
    } else {
      make_hull(m, Bpos, bp, !flag);
      make_hull(n, Apos, ap, flag);
    }
    double ans = 0;
    for (int i = 1; i < hull.size() - 1; ++i)
      ans += ccw(hull[0], hull[i], hull[i + 1]);
    if (ap[0] == ap[1]) {
      for (int i = 1; i < n - 1; ++i) ans += ccw(Apos[0], Apos[i], Apos[i + 1]);
    } else if (bp[0] == bp[1]) {
      for (int i = 1; i < m - 1; ++i) ans += ccw(Bpos[0], Bpos[i], Bpos[i + 1]);
    }
    fout.precision(1);
    fout << fixed << fabs(ans / 2) << '\n';
    convex.clear();
    hull.clear();
    ap.clear();
    bp.clear();
    fill(Apos, Apos + n, 0);
    fill(Bpos, Bpos + m, 0);
    fill(pos, pos + n + m, 0);
  }
  return 0;
}