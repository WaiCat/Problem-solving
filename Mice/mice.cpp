#include <limits.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point {
  int x, y;
};

// 직선이 다각형의 모서리를 지나는지 확인
bool intersects(Point a, Point b, Point c, Point d) {
  int det = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
  if (det == 0) return false;  // 평행 또는 일치

  double lambda =
      ((double)(d.y - c.y) * (d.x - a.x) + (c.x - d.x) * (d.y - a.y)) / det;
  double gamma =
      ((double)(a.y - b.y) * (d.x - a.x) + (b.x - a.x) * (d.y - a.y)) / det;

  return (0 < lambda && lambda < 1) && (0 < gamma && gamma < 1);
}

// 쥐와 쥐구멍 사이에 장애물이 있는지 판단
bool canSee(const Point& mouse, const Point& hole, const vector<Point>& house) {
  int n = house.size();
  for (int i = 0; i < n; ++i) {
    if (intersects(mouse, hole, house[i], house[(i + 1) % n])) {
      return false;
    }
  }
  return true;
}

// 최대 유량 알고리즘을 이용해 모든 쥐가 숨을 수 있는지 확인
bool canAllHide(int maxCap, const vector<Point>& holes,
                const vector<Point>& mice, const vector<Point>& house) {
  int h = holes.size(), m = mice.size();
  vector<vector<int>> capacity(h + m + 2, vector<int>(h + m + 2, 0));
  int source = h + m, sink = h + m + 1;

  // 쥐에서 구멍으로 용량 1의 엣지 생성
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < h; ++j) {
      if (canSee(mice[i], holes[j], house)) {
        capacity[i][m + j] = 1;
      }
    }
  }

  // 소스에서 쥐로, 구멍에서 싱크로 엣지 생성
  for (int i = 0; i < m; ++i) capacity[source][i] = 1;
  for (int j = 0; j < h; ++j) capacity[m + j][sink] = maxCap;

  int totalFlow = 0;
  while (true) {
    vector<int> parent(h + m + 2, -1);
    queue<int> q;
    q.push(source);
    parent[source] = -2;

    while (!q.empty() && parent[sink] == -1) {
      int current = q.front();
      q.pop();

      for (int next = 0; next < h + m + 2; ++next) {
        if (parent[next] == -1 && capacity[current][next] > 0) {
          parent[next] = current;
          q.push(next);
          if (next == sink) break;
        }
      }
    }

    if (parent[sink] == -1) break;

    int flow = INT_MAX;
    for (int node = sink; node != source; node = parent[node]) {
      flow = min(flow, capacity[parent[node]][node]);
    }

    for (int node = sink; node != source; node = parent[node]) {
      capacity[parent[node]][node] -= flow;
      capacity[node][parent[node]] += flow;
    }

    totalFlow += flow;
  }

  return totalFlow == m;
}

int main() {
  // ifstream fin("mice.inp");
  // ofstream fout("mice.out");

  ifstream fin("1.inp");
  ofstream fout("1.txt");

  int T;
  fin >> T;
  while (T--) {
    int N, M, H, K;
    fin >> N >> M >> H >> K;
    vector<Point> house(N), holes(H), mice(K);
    for (int i = 0; i < N; ++i) {
      fin >> house[i].x >> house[i].y;
    }
    for (int i = 0; i < H; ++i) {
      fin >> holes[i].x >> holes[i].y;
    }
    for (int i = 0; i < K; ++i) {
      fin >> mice[i].x >> mice[i].y;
    }

    fout << (canAllHide(M, holes, mice, house) ? "Possible" : "Impossible")
         << endl;
  }
  return 0;
}
