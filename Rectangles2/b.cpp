#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Event {
  int x, y1, y2;
  int type;  // 1 for opening, -1 for closing
};

bool compareEvent(const Event& a, const Event& b) { return a.x < b.x; }

int main() {
  // ifstream inp("rectangles.inp");
  // ofstream out("rectangles.out");
  ifstream inp("1.inp");
  ofstream out("1.txt");

  int n;
  inp >> n;

  vector<Event> events;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    inp >> x1 >> y1 >> x2 >> y2;
    events.push_back({x1, y1, y2, 1});
    events.push_back({x2, y1, y2, -1});
  }

  sort(events.begin(), events.end(), compareEvent);

  multimap<int, pair<int, int>> activeIntervals;
  int lastX = 0;
  int totalArea = 0;

  for (size_t i = 0; i < events.size(); i++) {
    Event& e = events[i];

    // Calculate current active y-length
    int currentYLength = 0;
    int lastY = -1;
    for (auto& interval : activeIntervals) {
      if (lastY < interval.first) {
        lastY = interval.first;
        currentYLength += interval.second.first - lastY;
        lastY = interval.second.first;
      } else if (lastY < interval.second.first) {
        currentYLength += interval.second.first - lastY;
        lastY = interval.second.first;
      }
    }

    // Add to total area
    if (i > 0) {
      totalArea += currentYLength * (e.x - lastX);
    }
    lastX = e.x;

    // Update active intervals
    if (e.type == 1) {
      activeIntervals.insert({e.y1, {e.y2, e.x}});
    } else {
      for (auto it = activeIntervals.begin(); it != activeIntervals.end();
           it++) {
        if (it->first == e.y1 && it->second.first == e.y2 &&
            it->second.second == e.x) {
          activeIntervals.erase(it);
          break;
        }
      }
    }
  }

  out << totalArea << endl;

  inp.close();
  out.close();

  return 0;
}
