#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 500;     // 최대 봉사 팀 수 + 지역 수
int capacity[MAX][MAX];  // 용량
int flow[MAX][MAX];      // 유량
vector<int> adj[MAX];    // 인접 리스트

bool bfs(int source, int sink, vector<int>& parent) {
  fill(parent.begin(), parent.end(), -1);
  queue<int> q;
  q.push(source);
  parent[source] = source;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int next : adj[cur]) {
      if (parent[next] == -1 && capacity[cur][next] > flow[cur][next]) {
        q.push(next);
        parent[next] = cur;
        if (next == sink) return true;
      }
    }
  }
  return false;
}

int maxFlow(int source, int sink, int size) {
  int totalFlow = 0;
  vector<int> parent(size);

  while (bfs(source, sink, parent)) {
    int amount = numeric_limits<int>::max();
    for (int p = sink; p != source; p = parent[p]) {
      amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
    }

    for (int p = sink; p != source; p = parent[p]) {
      flow[parent[p]][p] += amount;
      flow[p][parent[p]] -= amount;
    }

    totalFlow += amount;
  }
  return totalFlow;
}

bool isAssignmentPossible(int N, int P, int M, vector<int>& locationsPerPeriod,
                          vector<vector<pair<int, int>>>& preferences) {
  int source = N + P, sink = N + P + 1, size = N + P + 2;

  memset(capacity, 0, sizeof(capacity));
  memset(flow, 0, sizeof(flow));
  for (int i = 0; i < size; ++i) adj[i].clear();

  // 팀 노드와 소스 연결
  for (int i = 0; i < N; ++i) {
    adj[source].push_back(i);
    adj[i].push_back(source);
    capacity[source][i] = M;  // 각 팀은 최대 M 번까지 참여 가능
  }

  // 지역 노드와 싱크 연결
  for (int i = 0; i < P; ++i) {
    for (int j = 0; j < locationsPerPeriod[i]; ++j) {
      int loc_index = N + i;  // 지역 노드 시작 인덱스
      adj[loc_index].push_back(sink);
      adj[sink].push_back(loc_index);
      capacity[loc_index][sink] = 1;
    }
  }

  // 팀과 지역간 연결
  for (int i = 0; i < N; ++i) {
    for (auto& pr : preferences[i]) {
      int period = pr.first - 1, location = pr.second - 1;
      int loc_index = N + period;  // 해당 기간의 지역 노드 인덱스
      adj[i].push_back(loc_index);
      adj[loc_index].push_back(i);
      capacity[i][loc_index] = 1;
    }
  }

  int max_possible_assignments = maxFlow(source, sink, size);
  int total_locations = 0;
  for (int loc : locationsPerPeriod) total_locations += loc;

  return max_possible_assignments == total_locations;
}

int main() {
  // ifstream fin("service.inp");
  // ofstream fout("service.out");

  ifstream fin("0.inp");
  ofstream fout("0.txt");

  int T;  // 테스트 케이스 수
  fin >> T;

  while (T--) {
    int N, P, M;
    fin >> N >> P >> M;  // 팀 수, 기간 수, 최대 봉사 가능 횟수

    vector<int> locationsPerPeriod(P);
    for (int i = 0; i < P; i++) {
      fin >> locationsPerPeriod[i];  // 각 기간별 봉사 지역 수
    }

    vector<vector<pair<int, int>>> preferences(N);
    for (int i = 0; i < N; i++) {
      int numPreferences;
      fin >> numPreferences;
      for (int j = 0; j < numPreferences; j++) {
        int period, location;
        fin >> period >> location;
        preferences[i].push_back(make_pair(period, location));
      }
    }

    if (isAssignmentPossible(N, P, M, locationsPerPeriod, preferences)) {
      fout << "1\n";
    } else {
      fout << "0\n";
    }
  }

  fin.close();
  fout.close();
  return 0;
}
