#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <utility>

using namespace std;

struct Point {
  int x, y;
};

int calculateOrientation(long long x1, long long y1, long long x2, long long y2,
                         long long x3, long long y3) {
  long long result = (x2 - x1) * (y3 - y2) - (x3 - x2) * (y2 - y1);
  if (result > 0) return 1;
  if (result < 0) return -1;
  return 0;
}

int main() {
  ifstream fin("mice.inp");
  ofstream fout("mice.out");

  int T;
  fin >> T;

  while (T--) {
    int n, k, h, m, x, y;
    fin >> n >> k >> h >> m;
    Point houseVertices[n], hideouts[h], mice[m];

    for (int i = 0; i < n; i++) {
      fin >> x >> y;
      houseVertices[i] = {x, y};
    }

    for (int i = 0; i < h; i++) {
      fin >> x >> y;
      hideouts[i] = {x, y};
    }

    for (int i = 0; i < m; i++) {
      fin >> x >> y;
      mice[i] = {x, y};
    }

    int graph[h + m + 2][h + m + 2];
    memset(graph, 0, sizeof(graph));

    for (int i = 1; i <= h; i++) {
      graph[0][i] = k;
    }

    for (int i = h + 1; i < h + m + 1; i++) {
      graph[i][h + m + 1] = 1;
    }

    for (int i = 0; i < h; i++) {
      int hideoutX = hideouts[i].x;
      int hideoutY = hideouts[i].y;
      for (int j = 0; j < m; j++) {
        int mouseX = mice[j].x;
        int mouseY = mice[j].y;
        bool canHide = true;

        for (int p = 0; p < n; p++) {
          int x1 = houseVertices[p].x;
          int y1 = houseVertices[p].y;
          int x2 = houseVertices[(p + 1) % n].x;
          int y2 = houseVertices[(p + 1) % n].y;

          if (calculateOrientation(x1, y1, hideoutX, hideoutY, x2, y2) == 0)
            continue;
          if (calculateOrientation(x1, y1, x2, y2, hideoutX, hideoutY) *
                  calculateOrientation(x1, y1, x2, y2, mouseX, mouseY) >
              0)
            continue;
          if (calculateOrientation(hideoutX, hideoutY, mouseX, mouseY, x1, y1) *
                  calculateOrientation(hideoutX, hideoutY, mouseX, mouseY, x2,
                                       y2) >
              0)
            continue;
          canHide = false;
          break;
        }
        if (canHide) {
          graph[i + 1][h + j + 1] = 1;
        }
      }
    }

    int totalHideouts = 0, hideoutCount, nextHideout;
    while (true) {
      int previous[h + m + 2];
      memset(previous, -1, sizeof(previous));

      deque<pair<int, int>> queue;
      queue.push_back({0, k + 1});

      while (!queue.empty()) {
        int current = queue.front().first;
        hideoutCount = queue.front().second;
        queue.pop_front();

        if (graph[current][h + m + 1]) {
          hideoutCount = min(hideoutCount, graph[current][h + m + 1]);
          previous[h + m + 1] = current;
          break;
        }
        for (nextHideout = 1; nextHideout < h + m + 1; nextHideout++) {
          if (previous[nextHideout] == -1 && graph[current][nextHideout]) {
            previous[nextHideout] = current;
            queue.push_back(
                {nextHideout, min(hideoutCount, graph[current][nextHideout])});
          }
        }
        if (previous[h + m + 1] != -1) break;
      }
      if (previous[h + m + 1] == -1) break;

      totalHideouts += hideoutCount;
      nextHideout = h + m + 1;
      while (true) {
        int current = previous[nextHideout];
        graph[current][nextHideout] -= hideoutCount;
        graph[nextHideout][current] += hideoutCount;
        nextHideout = current;
        if (nextHideout == 0) break;
      }
    }
    if (totalHideouts == m)
      fout << "Possible" << '\n';
    else
      fout << "Impossible" << '\n';
  }
}
