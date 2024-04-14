#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Event {
  int x;
  int heightChange;
  bool operator<(const Event& other) const {
    return x < other.x || (x == other.x && heightChange > other.heightChange);
  }
};

int main() {
  ifstream fin("contour.inp");
  ofstream fout("contour.out");

  vector<vector<Event>> test_cases;
  vector<Event> events;

  // 입력 처리
  int x1, h, x2;
  while (fin >> x1 >> h >> x2) {
    if (x1 == 0 && h == 0 && x2 == 0) {
      if (!events.empty()) {
        test_cases.push_back(events);
        events.clear();
      }
    } else {
      events.push_back(Event{x1, h});
      events.push_back(Event{x2, -h});
    }
  }

  if (!events.empty()) {
    test_cases.push_back(events);
  }

  fin.close();

  int case_number = 1;
  for (auto& events : test_cases) {
    sort(events.begin(), events.end());

    map<int, int> height_count;
    int current_max_height = 0;
    int last_x = 0;
    long long current_area = 0;
    vector<long long> areas;

    for (size_t i = 0; i < events.size(); ++i) {
      Event& e = events[i];

      int width = (i > 0) ? e.x - last_x : 0;
      if (current_max_height > 0 && width > 0) {
        current_area += (long long)width * current_max_height;
      }

      if (e.heightChange > 0) {
        height_count[e.heightChange]++;
      } else {
        height_count[-e.heightChange]--;
        if (height_count[-e.heightChange] == 0) {
          height_count.erase(-e.heightChange);
        }
      }

      if (!height_count.empty()) {
        current_max_height = height_count.rbegin()->first;
      } else {
        current_max_height = 0;
        if (current_area > 0) {
          areas.push_back(current_area);
          current_area = 0;
        }
      }

      last_x = e.x;
    }

    fout << "Test Case #" << case_number++ << " :";
    for (auto area : areas) {
      fout << " " << area;
    }
    fout << endl;
  }

  fout.close();

  return 0;
}
