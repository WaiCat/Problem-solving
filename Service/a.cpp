#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_TEAMS = 400;
const int MAX_PERIODS = 100;
const int MAX_REGIONS = 100;

struct Application {
  int period, region;
};

vector<Application> applications[MAX_TEAMS + 1];
int service_regions[MAX_PERIODS + 1];
bool visited[MAX_TEAMS + 1];
int assigned[MAX_REGIONS + 1][MAX_PERIODS + 1];
int team_limit[MAX_TEAMS + 1];

bool canAssign(int team, int max_services) {
  if (team_limit[team] >= max_services) {
    return false;
  }
  return true;
}

bool tryAssign(int team, int max_services) {
  visited[team] = true;
  for (const auto& app : applications[team]) {
    int period = app.period;
    int region = app.region;
    if (assigned[region][period] == -1 ||
        (!visited[assigned[region][period]] &&
         tryAssign(assigned[region][period], max_services))) {
      assigned[region][period] = team;
      return true;
    }
  }
  return false;
}

int main() {
  ifstream input("2.inp");
  ofstream output("2.txt");

  int T;
  input >> T;
  while (T--) {
    int N, P, M;
    input >> N >> P >> M;

    for (int i = 1; i <= N; i++) {
      applications[i].clear();
    }

    vector<int> regions(P + 1);
    for (int i = 1; i <= P; i++) {
      input >> regions[i];
    }

    for (int i = 1; i <= N; i++) {
      int count;
      input >> count;
      for (int j = 0; j < count; j++) {
        int p, r;
        input >> p >> r;
        applications[i].push_back({p, r});
      }
    }

    bool possible = true;
    memset(assigned, -1, sizeof(assigned));
    for (int i = 1; i <= N; i++) {
      memset(visited, 0, sizeof(visited));
      if (!tryAssign(i, M)) {
        possible = false;
        break;
      }
    }

    if (possible) {
      output << 1 << endl;
    } else {
      output << 0 << endl;
    }
  }

  input.close();
  output.close();
  return 0;
}
