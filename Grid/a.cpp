#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#define endl '\n'
#define CONNECT 1
#define DISCONNECT 0
#define ESSENTIAL 2
#define MODULE 1000000007
#define ll long long
using namespace std;

ifstream fin;
ofstream fout;

void set_map(vector<vector<int>> &arr, int a, int b) {
  for (int i = 0; i < a; i++) {
    int x, y;
    fin >> x >> y;
    arr[y][x] = ESSENTIAL;
  }
  for (int i = 0; i < b; i++) {
    int x, y;
    fin >> x >> y;
    arr[y][x] = DISCONNECT;
  }
}

void display(vector<vector<int>> map, int x, int y) {  // dim, col, row
  for (int i = y; i >= 0; i--) {
    for (int j = 0; j <= x; j++) {
      cout << map[i][j];
    }
    cout << endl;
  }
}

int main() {
  fin.open("1.inp");
  fout.open("grid.out");
  int T;
  fin >> T;
  while (T > 0) {
    int x, y, a, b, k;
    fin >> x >> y >> a >> b >> k;  // (x,y) : 목적지 좌표 / a : 지나야 될 곳 / b
                                   // : 지나면 안되는 곳 / k : 최소 개수
    vector<vector<int>> map(y + 1, vector<int>(x + 1, CONNECT));
    set_map(map, a, b);
    // vector<vector<vector<int>>> vec3D(depth, vector<vector<int>>(rows,
    // vector<int>(cols, initial_value)));
    vector<vector<vector<ll>>> dp(
        k + 1, vector<vector<ll>>(
                   y + 1, vector<ll>(x + 1, DISCONNECT)));  // dim , col, row
    bool flag = true;
    int d = 0;
    for (int i = 0; i < y + 1; i++) {
      if (map[i][0] == DISCONNECT || !flag) {
        dp[d][i][0] = DISCONNECT;
        flag = false;
      } else if (map[i][0] == ESSENTIAL) {
        d++;
        if (d == k + 1) d--;
        dp[d][i][0] = CONNECT;
      } else
        dp[d][i][0] = CONNECT;
    }
    flag = true;
    d = 0;
    for (int i = 0; i < x + 1; i++) {
      if (map[0][i] == DISCONNECT || !flag) {
        dp[d][0][i] = DISCONNECT;
        flag = false;
      } else if (map[0][i] == ESSENTIAL) {
        d++;
        if (d == k + 1) d--;
        dp[d][0][i] = CONNECT;
      } else
        dp[d][0][i] = CONNECT;
    }

    for (int i = 1; i < y + 1; i++) {    // column
      for (int j = 1; j < x + 1; j++) {  // row
        int cur_value = map[i][j];
        if (cur_value == CONNECT) {  // 연결
          for (int dim = 0; dim < k + 1; dim++) {
            dp[dim][i][j] =
                (dp[dim][i - 1][j] % MODULE + dp[dim][i][j - 1] % MODULE) %
                MODULE;
          }
        } else if (cur_value == DISCONNECT) {  // 끊어졌을 때

        } else if (cur_value == ESSENTIAL) {  // 필수적으로 가야될 때
          for (int dim = 0; dim < k + 1; dim++) {
            dp[dim][i][j] =
                (dp[dim][i - 1][j] % MODULE + dp[dim][i][j - 1] % MODULE) %
                MODULE;
          }
          for (int dim = k; dim >= 0; dim--) {
            if (dim == 0) {
              dp[dim][i][j] = 0;
            } else if (dim == k) {
              dp[dim][i][j] =
                  (dp[dim][i][j] % MODULE + dp[dim - 1][i][j] % MODULE) %
                  MODULE;
            } else {
              dp[dim][i][j] = dp[dim - 1][i][j];
            }
          }
        }
      }
    }
    fout << dp[k][y][x] << endl;
    // display(map, x, y);
    T--;
  }

  fout.close();
  fin.close();
}