#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void dfs1(int v, vector<vector<int>>& adj, vector<bool>& visited,
          stack<int>& Stack) {
  visited[v] = true;
  for (int u : adj[v]) {
    if (!visited[u]) dfs1(u, adj, visited, Stack);
  }
  Stack.push(v);
}

void dfs2(int v, vector<vector<int>>& adj, vector<bool>& visited) {
  visited[v] = true;
  for (int u : adj[v]) {
    if (!visited[u]) dfs2(u, adj, visited);
  }
}

int findSCCs(int V, vector<vector<int>>& adj) {
  stack<int> Stack;
  vector<bool> visited(V, false);

  for (int i = 0; i < V; i++) {
    if (!visited[i]) dfs1(i, adj, visited, Stack);
  }

  vector<vector<int>> adjT(V);
  for (int v = 0; v < V; v++) {
    for (int u : adj[v]) {
      adjT[u].push_back(v);
    }
  }

  fill(visited.begin(), visited.end(), false);
  int sccCount = 0;
  while (!Stack.empty()) {
    int v = Stack.top();
    Stack.pop();
    if (!visited[v]) {
      dfs2(v, adjT, visited);
      sccCount++;
    }
  }

  return sccCount;
}

int main() {
  ifstream fin("scc.inp");
  ofstream fout("scc.out");

  int V, E;
  fin >> V >> E;

  vector<vector<int>> adj(V);
  for (int i = 0; i < E; i++) {
    int u, v;
    fin >> u >> v;
    adj[u].push_back(v);
  }

  int sccCount = findSCCs(V, adj);
  fout << sccCount << endl;

  fin.close();
  fout.close();

  return 0;
}
