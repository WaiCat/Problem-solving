#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool isValid(vector<vector<int>>& teams, vector<vector<int>>& areas,
             vector<int>& used, int idx, int P, int M) {
  // 모든 팀에 대해 확인
  for (int i = 0; i < P; ++i) {
    // 아직 사용되지 않은 팀이면서 해당 지역을 지원하는 경우
    if (!used[i] && teams[i][idx] <= M) {
      // 해당 지역이 이미 다른 팀에 배정된 경우
      if (areas[idx][teams[i][idx]] > 0) {
        return false;
      }
    }
  }
  return true;
}

bool backtrack(vector<vector<int>>& teams, vector<vector<int>>& areas,
               vector<int>& used, int idx, int P, int M, int N) {
  // 모든 지역을 확인한 경우
  if (idx == N) {
    return true;
  }

  // 해당 지역에 대해 팀을 배정하는 경우를 확인
  for (int i = 0; i < P; ++i) {
    // 아직 사용되지 않은 팀이면서 해당 지역을 지원하는 경우
    if (!used[i] && teams[i][idx] <= M) {
      // 해당 지역을 해당 팀에 배정
      areas[idx][teams[i][idx]]++;
      used[i] = 1;

      // 다음 지역을 확인
      if (backtrack(teams, areas, used, idx + 1, P, M, N)) {
        return true;
      }

      // 해당 지역을 해당 팀에 배정하지 않음 (백트래킹)
      areas[idx][teams[i][idx]]--;
      used[i] = 0;
    }
  }

  // 어떠한 팀에도 해당 지역을 배정할 수 없는 경우
  return false;
}

int main() {
  // ifstream fin("service.inp");
  // ofstream fout("service.out");

  ifstream fin("3.inp");
  ofstream fout("3.txt");

  int T;
  fin >> T;

  for (int t = 0; t < T; ++t) {
    int P, N, M;
    fin >> P >> N >> M;

    vector<vector<int>> teams(P, vector<int>(N, 0));
    vector<vector<int>> areas(N, vector<int>(M + 1, 0));
    vector<int> used(P, 0);

    // 팀이 지원하는 지역 정보 입력
    for (int i = 0; i < P; ++i) {
      int K;
      fin >> K;
      for (int j = 0; j < K; ++j) {
        int idx;
        fin >> idx;
        fin >> teams[i][idx - 1];
      }
    }

    // 백트래킹을 이용한 지역별 팀 배정 시도
    if (backtrack(teams, areas, used, 0, P, M, N)) {
      fout << "1" << endl;  // 가능한 배정이 있는 경우
    } else {
      fout << "0" << endl;  // 가능한 배정이 없는 경우
    }
  }

  return 0;
}
