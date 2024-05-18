#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Path {
  int target, capacity;
  int reverse_index;
};

int Locations[51];
int total_capacity;
int END_INDEX;
vector<Path> paths[10005];
vector<int> node_numbers;
vector<int> levels;

int depth_first_search(int node, int flow) {
  if (node == END_INDEX) return flow;

  for (int& idx = node_numbers[node]; idx < paths[node].size(); ++idx) {
    Path& edge = paths[node][idx];

    if (edge.capacity > 0 && levels[edge.target] > levels[node]) {
      int min_flow = depth_first_search(edge.target, min(flow, edge.capacity));
      if (min_flow > 0) {
        edge.capacity -= min_flow;
        paths[edge.target][edge.reverse_index].capacity += min_flow;
        return min_flow;
      }
    }
  }
  return 0;
}

void add_edge(int start, int end, int capacity) {
  paths[start].push_back({end, capacity, (int)paths[end].size()});
  paths[end].push_back({start, 0, (int)paths[start].size() - 1});
}

bool breadth_first_search() {
  queue<int> q;
  levels.assign(10005, -1);
  levels[0] = 0;
  q.push(0);

  while (!q.empty()) {
    int current = q.front();
    q.pop();

    for (const auto& edge : paths[current]) {
      if (levels[edge.target] == -1 && edge.capacity > 0) {
        levels[edge.target] = levels[current] + 1;
        q.push(edge.target);
      }
    }
  }
  return levels[END_INDEX] != -1;
}

int main(void) {
  ifstream fin("service.inp");
  ofstream fout("service.out");

  int T;
  fin >> T;
  while (T--) {
    int N, P, M;
    fin >> N >> P >> M;
    END_INDEX = N + N * P + total_capacity + 1;
    total_capacity = 0;
    for (int i = 0; i < 10005; i++) {
      paths[i].clear();
    }
    int x, y, z;
    for (int i = 0; i < P; i++) {
      fin >> x;
      total_capacity += x;
      Locations[i + 1] = total_capacity;
    }
    for (int i = 0; i < N; i++) {
      add_edge(0, i + 1, M);
      fin >> x;
      for (int j = 1; j <= P; j++) {
        add_edge(i + 1, N + i * P + j, 1);
      }
      for (int j = 0; j < x; j++) {
        fin >> y >> z;
        add_edge(N + i * P + y, N + N * P + z + Locations[y - 1], 1);
      }
    }
    for (int i = 1; i <= total_capacity; i++) {
      add_edge(N + N * P + i, END_INDEX, 1);
    }

    int max_flow = 0;

    while (true) {
      node_numbers.clear();
      node_numbers.resize(10005, 0);
      if (!breadth_first_search()) break;
      while (true) {
        int additional_flow = depth_first_search(0, 1e9);
        if (additional_flow == 0) break;
        max_flow += additional_flow;
      }
    }
    if (max_flow < total_capacity) {
      fout << "0" << endl;
    } else {
      fout << "1" << endl;
    }
  }
}
