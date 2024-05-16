#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 변수 선언
vector<vector<vector<int>>> v;
bool home[101][101];  // 방문 여부를 저장하는 2차원 bool 배열
int done[101][101];   // 매칭 상태를 저장하는 2차원 int 배열

// 깊이 우선 탐색(DFS) 함수 정의
bool dfs(int x) {
  for (int j = 0; j < v[x].size(); j++) {
    for (int i = 0; i < v[x][j].size(); i++) {
      int now = v[x][j][i];        // 현재 노드 x와 연결된 노드
      if (home[j][now]) continue;  // 이미 방문한 노드면 건너뜀
      home[j][now] = true;  // 현재 노드 now를 방문했음을 표시

      // 현재 노드 now가 매칭되어 있지 않거나, 매칭된 노드에 대해 더 깊이 탐색
      // 가능하면
      if (done[now] == 0 || dfs(done[now])) {
        done[now] = x;  // 현재 노드 now와 노드 x를 매칭
        return true;    // 매칭 성공
      }
    }
  }

  return false;  // 매칭 실패
}

int main() {
  // ifstream fin("service.inp");
  // ofstream fout("service.out");

  ifstream fin("0.inp");
  ofstream fout("0.txt");

  int T;
  fin >> T;
  while (T--) {
    int N, P, M, l, x, y;

    fin >> N >> P >> M;  // N과 M을 입력받음

    // 각 노드에 대해 연결된 노드를 입력받아 그래프를 구성
    for (int i = 1; i <= N; i++) {
      fin >> l;  // 노드 i에 연결된 노드 수를 입력받음
      vector<int> tmp;
      vector<vector<int>> tmp2;
      int index = 1;
      for (int j = 0; j < l; j++) {
        fin >> x >> y;         // 연결된 노드 y를 입력받음
        v[i][x].push_back(y);  // 그래프에 추가
      }
    }

    // 각 노드에 대해 매칭을 초기화하고 DFS 수행
    for (int i = 1; i <= N; i++) {
      // 매칭 상태와 방문 여부 초기화
      for (int i = 0; i < 101; ++i) {
        fill(done[i], done[i] + 101, false);
      }
      dfs(i);  // 노드 i에 대해 DFS 수행
    }

    // 매칭된 노드 수를 계산
    int ans = 0;
    for (int i = 1; i <= M; i++) {
      if (done[i] > 0) ans++;  // 매칭된 노드가 있으면 카운트 증가
    }
    fout << ans;  // 매칭된 노드 수 출력
  }

  return 0;
}
