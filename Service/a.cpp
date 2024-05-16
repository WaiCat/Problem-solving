#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#define MAX 101

using namespace std;

struct Node {
    int layer;
    int vertex;
};

vector<Node> vtx[MAX][MAX]; // 층별 정점 vtx
int slt[MAX][MAX]; // vtx가 점유하고 있는 정점
bool done[MAX][MAX]; // 처리 여부
int n, m, k; // 정점 수, 간선 수, 층 수

bool dfs(int layer, int x) {
    // 연결된 모든 정점에 대해 들어갈 수 있는지 시도
    for (const Node& node : vtx[layer][x]) {
        int l = node.layer;
        int p = node.vertex;
        // 이미 처리한 정점은 고려하지 않음
        if (done[l][p]) continue;
        done[l][p] = true;
        // 비어있거나 점유 정점에 더 들어갈 공간이 있는 경우
        if (slt[l][p] == 0 || dfs(slt[l][p] / MAX, slt[l][p] % MAX)) {
            slt[l][p] = layer * MAX + x;
            return true;
        }
    }
    return false;
}

int main() {
    // ifstream fin("service.inp");
  // ofstream fout("service.out");

  ifstream fin("0.inp");
  ofstream fout("0.txt");

  int T;
  fin >> T;

  while(T--){

  fin >> k >> n >> m;

  for (int i = 0; i < m; i++) {
      int u_layer, u, v_layer, v;
      fin >> u_layer >> u >> v_layer >> v;
      vtx[u_layer][u].push_back({v_layer, v});
    }

    int cnt = 0; // 매칭 수
    memset(slt, 0, sizeof(slt));

    for (int layer = 0; layer < k; layer++) {
        for (int i = 1; i <= n; i++) {
            memset(done, 0, sizeof(done));
            if (dfs(layer, i)) cnt++;
        }
    }

    fout << "매칭 " << cnt << "번 성공" << endl;
    for (int l = 0; l < k; l++) {
        for (int i = 1; i <= n; i++) {
            if (slt[l][i] != 0) {
                fout << "층 " << l << "의 정점 " << i << " => "
                     << "층 " << slt[l][i] / MAX << "의 정점 " << slt[l][i] % MAX << endl;
            }
        }
    }
  }

    return 0;
}
