#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Event {
  int x, y1, y2;
  bool is_start;

  bool operator<(const Event& other) const {
    return x < other.x || (x == other.x && is_start > other.is_start);
  }
};

struct Segment {
  int y, count;
  Segment *left, *right;

  Segment(int y) : y(y), count(0), left(nullptr), right(nullptr) {}
};

Segment* buildTree(int low, int high, vector<int>& coords) {
  if (low == high) return new Segment(coords[low]);
  int mid = (low + high) / 2;
  Segment* node = new Segment(0);
  node->left = buildTree(low, mid, coords);
  node->right = buildTree(mid + 1, high, coords);
  return node;
}

void update(Segment* node, int y, int val, vector<int>& coords, int low,
            int high) {
  if (low == high) {
    if (coords[low] == y) node->count += val;
    return;
  }
  int mid = (low + high) / 2;
  if (y <= coords[mid]) {
    update(node->left, y, val, coords, low, mid);
  } else {
    update(node->right, y, val, coords, mid + 1, high);
  }

  node->count = (node->left ? node->left->count : 0) +
                (node->right ? node->right->count : 0);
}

int query(Segment* root) {
  if (root->count > 0) {
    return root->y;
  } else {
    return query(root->left) + query(root->right);
  }
}

int main() {
  // ifstream fin("rectangles.inp");
  // ofstream fout("rectangles.out");

  ifstream fin("0.inp");
  ofstream fout("0.txt");

  int n;
  fin >> n;
  vector<Event> events;
  set<int> ys;

  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    fin >> x1 >> y1 >> x2 >> y2;
    events.push_back({x1, y1, y2, true});
    events.push_back({x2, y1, y2, false});
    ys.insert(y1);
    ys.insert(y2);
  }

  vector<int> coords(ys.begin(), ys.end());
  sort(events.begin(), events.end());

  Segment* root = buildTree(0, coords.size() - 1, coords);
  int last_x = 0;
  int area = 0;

  for (const auto& e : events) {
    int current_x = e.x;
    int width = current_x - last_x;
    if (width > 0) {
      int height = query(root);
      area += width * height;
      last_x = current_x;
    }
    update(root, e.y1, e.is_start ? 1 : -1, coords, 0, coords.size() - 1);
    update(root, e.y2, e.is_start ? -1 : 1, coords, 0, coords.size() - 1);
  }

  fout << area << endl;
  fin.close();
  fout.close();
  return 0;
}
