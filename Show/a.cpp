#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

const int MAX_N = 10010; // 전구의 최대 개수

vector<int> adj[MAX_N * 2];
int dfsn[MAX_N * 2], finished[MAX_N * 2], scc[MAX_N * 2];
int cnt, scc_cnt;
stack<int> stk;

int NOT(int x) {
    return x % 2 ? x - 1 : x + 1;
}

int dfs(int curr) {
    dfsn[curr] = ++cnt;
    stk.push(curr);

    int result = dfsn[curr];
    for (int next : adj[curr]) {
        if (dfsn[next] == 0) result = min(result, dfs(next));
        else if (!finished[next]) result = min(result, dfsn[next]);
    }

    if (result == dfsn[curr]) {
        while (true) {
            int top = stk.top();
            stk.pop();
            finished[top] = 1;
            scc[top] = scc_cnt;
            if (top == curr) break;
        }
        ++scc_cnt;
    }

    return result;
}

void add_edge(int u, int v) {
    adj[u].push_back(v);
}

bool solve_2SAT(int N) {
    memset(dfsn, 0, sizeof(dfsn));
    memset(finished, 0, sizeof(finished));
    memset(scc, 0, sizeof(scc));
    cnt = scc_cnt = 0;

    for (int i = 0; i < N * 2; ++i) {
        if (dfsn[i] == 0) dfs(i);
    }

    for (int i = 0; i < N; ++i) {
        if (scc[i * 2] == scc[i * 2 + 1]) return false;
    }

    return true;
}

int main() {
    ifstream fin("1.inp");
    ofstream fout("1.txt");

    int T;
    fin >> T;

    while (T--) {
        int N, M;
        fin >> N >> M;

        // 그래프 초기화
        for (int i = 0; i < N * 2; ++i) {
            adj[i].clear();
        }

        for (int i = 0; i < M; ++i) {
            int a, b;
            char ca, cb;
            fin >> a >> ca >> b >> cb;
            --a; --b;

            // 각 전구의 색에 대한 불리언 변수 번호
            int u = a * 2 + (ca == 'R' ? 0 : 1);
            int v = b * 2 + (cb == 'R' ? 0 : 1);

            // u 또는 v가 참이면, NOT(u) 또는 NOT(v)도 참이어야 함
            add_edge(NOT(u), v);
            add_edge(NOT(v), u);
        }

        if (solve_2SAT(N)) {
            fout << 1 << endl;
        } else {
            fout << -1 << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
