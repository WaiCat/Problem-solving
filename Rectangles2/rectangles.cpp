#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Event {
  int x, y1, y2, type;
  Event(int x, int y1, int y2, int type) : x(x), y1(y1), y2(y2), type(type) {}
  bool operator<(const Event& e) const { return x < e.x; }
};

struct SegmentTree {
  vector<int> tree, count;
  int size;
  SegmentTree(int n) : size(n) {
    tree.resize(4 * n);
    count.resize(4 * n);
  }
  void update(int node, int start, int end, int left, int right, int value) {
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
      count[node] += value;
    } else {
      int mid = (start + end) / 2;
      update(2 * node, start, mid, left, right, value);
      update(2 * node + 1, mid + 1, end, left, right, value);
    }
    if (count[node] > 0)
      tree[node] = end - start + 1;
    else if (start != end)
      tree[node] = tree[2 * node] + tree[2 * node + 1];
    else
      tree[node] = 0;
  }
  int query() { return tree[1]; }
};

int main() {
  ifstream fin("rectangles.inp");
  ofstream fout("rectangles.out");

  int n;
  fin >> n;
  vector<Event> events;
  int minY = INT_MAX, maxY = INT_MIN;

  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;
    x1 += 10000;
    x2 += 10000;
    y1 += 10000;
    y2 += 10000;
    events.emplace_back(x1, y1, y2 - 1, 1);
    events.emplace_back(x2, y1, y2 - 1, -1);
    minY = min(minY, y1);
    maxY = max(maxY, y2);
  }

  sort(events.begin(), events.end());

  SegmentTree st(maxY + 1);
  int lastX = events[0].x;
  long long area = 0;
  for (auto& e : events) {
    int currentX = e.x;
    if (lastX != currentX) {
      area += (long long)st.query() * (currentX - lastX);
      lastX = currentX;
    }
    st.update(1, minY, maxY, e.y1, e.y2, e.type);
  }

  fout << area << endl;
  return 0;
}
