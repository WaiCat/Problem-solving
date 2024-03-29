#include <fstream>
#include <iostream>
#include <vector>

#define MOD 1000000007
#define POINT 0
#define PASSPOINT 1
#define FORBIDDENPOINT 2

using namespace std;

int main() {
  ifstream fin("2.inp");
  ofstream fout("2.txt");

  int test_cases;
  fin >> test_cases;

  for (int t = 0; t < test_cases; ++t) {
    int rows, cols, a, b, k;
    fin >> rows >> cols >> a >> b >> k;

    vector<vector<int>> state(rows + 1, vector<int>(cols + 1));
    vector<vector<vector<int>>> grid(
        rows + 1, vector<vector<int>>(cols + 1, vector<int>(k + 1)));

    for (int i = 0; i < a; ++i) {
      int x, y;
      fin >> x >> y;
      state[x][y] = PASSPOINT;
    }

    for (int i = 0; i < b; ++i) {
      int x, y;
      fin >> x >> y;
      state[x][y] = FORBIDDENPOINT;
    }

    grid[0][0][0] = 1;
    int kn = 0;

    for (int i = 1; i <= rows; ++i) {
      if (state[i][0] == POINT) {
        grid[i][0][kn] = grid[i - 1][0][kn];
      } else if (state[i][0] == PASSPOINT) {
        kn++;
        if (kn > k) {
          kn--;
        }
        grid[i][0][kn] = grid[i - 1][0][kn - 1];
      } else {
        break;
      }
    }

    kn = 0;
    for (int i = 1; i <= cols; ++i) {
      if (state[0][i] == POINT) {
        grid[0][i][kn] = grid[0][i - 1][kn];
      } else if (state[0][i] == PASSPOINT) {
        kn++;
        if (kn > k) {
          kn--;
        }
        grid[0][i][kn] = grid[0][i - 1][kn - 1];
      } else {
        break;
      }
    }

    for (int i = 1; i <= rows; i++) {
      for (int v = 1; v <= cols; v++) {
        if (state[i][v] == POINT) {
          for (int l = 0; l <= k; l++) {
            grid[i][v][l] =
                (grid[i - 1][v][l] % MOD + grid[i][v - 1][l] % MOD) % MOD;
          }
        } else if (state[i][v] == PASSPOINT) {
          for (int l = 0; l <= k; l++) {
            grid[i][v][l] =
                (grid[i - 1][v][l] % MOD + grid[i][v - 1][l] % MOD) % MOD;
          }
          grid[i][v][k - 1] += grid[i][v][k];
          for (int l = k; l > 0; l--) {
            grid[i][v][l] = grid[i][v][l - 1];
          }
          grid[i][v][0] = 0;
        }
      }
    }

    fout << grid[rows][cols][k] << endl;
  }

  fin.close();
  fout.close();

  return 0;
}
