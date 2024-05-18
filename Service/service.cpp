#include <algorithm>
#include <climits>  // INT_MAX를 사용하기 위해 추가
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int MAX_WORKERS = 100;
const int MAX_PROJECTS = 2500;
const int WORKER_PROJECT_OFFSET = 2600;
const int TOTAL_NODES = 2652;

const int SOURCE = TOTAL_NODES - 2;
const int SINK = TOTAL_NODES - 1;

int testCases, numWorkers, numProjects, maxProjectsPerWorker;
int capacity[TOTAL_NODES][TOTAL_NODES], flow[TOTAL_NODES][TOTAL_NODES];
vector<int> adj[TOTAL_NODES];
vector<int> cumulativeProjects;

void initializeGraph() {
  for (int i = 0; i < TOTAL_NODES; ++i) adj[i].clear();
  fill(&capacity[0][0], &capacity[TOTAL_NODES - 1][TOTAL_NODES], 0);
  fill(&flow[0][0], &flow[TOTAL_NODES - 1][TOTAL_NODES], 0);
}

bool bfs(vector<int>& parent) {
  fill(parent.begin(), parent.end(), -1);
  queue<int> q;
  q.push(SOURCE);
  parent[SOURCE] = SOURCE;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (int next : adj[cur]) {
      if (parent[next] == -1 && capacity[cur][next] > flow[cur][next]) {
        parent[next] = cur;
        if (next == SINK) return true;
        q.push(next);
      }
    }
  }
  return false;
}

int edmondsKarp() {
  int maxFlow = 0;
  vector<int> parent(TOTAL_NODES);

  while (bfs(parent)) {
    int pathFlow = INT_MAX;
    for (int v = SINK; v != SOURCE; v = parent[v]) {
      int u = parent[v];
      pathFlow = min(pathFlow, capacity[u][v] - flow[u][v]);
    }

    for (int v = SINK; v != SOURCE; v = parent[v]) {
      int u = parent[v];
      flow[u][v] += pathFlow;
      flow[v][u] -= pathFlow;
    }
    maxFlow += pathFlow;
  }

  return maxFlow;
}

int main() {
  ifstream fin("service.inp");
  ofstream fout("service.out");

  fin >> testCases;
  while (testCases--) {
    fin >> numWorkers >> numProjects >> maxProjectsPerWorker;
    initializeGraph();

    cumulativeProjects = vector<int>(numProjects + 1, 0);
    for (int i = 1; i <= numProjects; ++i) {
      fin >> cumulativeProjects[i];
      cumulativeProjects[i] += cumulativeProjects[i - 1];
    }

    for (int worker = 0; worker < numWorkers; ++worker) {
      capacity[SOURCE][worker] = maxProjectsPerWorker;
      adj[SOURCE].push_back(worker);
      adj[worker].push_back(SOURCE);

      set<int> uniqueProjects;
      int accessibleProjects;
      fin >> accessibleProjects;

      for (int j = 0; j < accessibleProjects; ++j) {
        int project, time;
        fin >> project >> time;
        if (time >
            cumulativeProjects[project] - cumulativeProjects[project - 1])
          continue;
        project--;
        time += MAX_WORKERS - 1;
        uniqueProjects.insert(project);

        int virtualProjectNode = time + cumulativeProjects[project];
        capacity[project + WORKER_PROJECT_OFFSET][virtualProjectNode] = 1;
        adj[project + WORKER_PROJECT_OFFSET].push_back(virtualProjectNode);
        adj[virtualProjectNode].push_back(project + WORKER_PROJECT_OFFSET);
      }

      for (int project : uniqueProjects) {
        capacity[worker][project + WORKER_PROJECT_OFFSET] = 1;
        adj[worker].push_back(project + WORKER_PROJECT_OFFSET);
        adj[project + WORKER_PROJECT_OFFSET].push_back(worker);
      }
    }

    for (int i = MAX_WORKERS; i < MAX_WORKERS + cumulativeProjects[numProjects];
         ++i) {
      capacity[i][SINK] = 1;
      adj[i].push_back(SINK);
      adj[SINK].push_back(i);
    }
    int totalProjectCapacity = cumulativeProjects[numProjects];
    int maxFlow = edmondsKarp();

    if (maxFlow == totalProjectCapacity)
      fout << 1 << '\n';
    else
      fout << 0 << '\n';
  }

  return 0;
}
