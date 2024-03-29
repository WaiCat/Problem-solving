#include <fstream>
#include <iostream>
#include <vector>

#define MOD 1000000007

using namespace std;

int main() {
  ifstream fin("grid.inp");
  ofstream fout("grid.out");

  int testCases;
  fin >> testCases;

  for (int testCase = 0; testCase < testCases; ++testCase) {
    int x, y, a, b, t;
    fin >> x >> y >> a >> b >> t;

    vector<vector<int>> state(x + 1, vector<int>(y + 1));
    vector<vector<vector<int>>> grid(
        x + 1, vector<vector<int>>(y + 1, vector<int>(t + 1)));

    for (int i = 0; i < a; ++i) {
      int x, y;
      fin >> x >> y;
      state[x][y] = 1;
    }

    for (int i = 0; i < b; ++i) {
      int x, y;
      fin >> x >> y;
      state[x][y] = 2;
    }

    grid[0][0][0] = 1;
    int remainingMoves = 0;

    for (int i = 1; i <= x; ++i) {
      if (state[i][0] == 0) {
        grid[i][0][remainingMoves] = 1;
      } else if (state[i][0] == 1) {
        remainingMoves++;
        if (remainingMoves > t) {
          remainingMoves--;
        }
        grid[i][0][remainingMoves] = 1;
      } else {
        break;
      }
    }

    remainingMoves = 0;
    for (int i = 1; i <= y; ++i) {
      if (state[0][i] == 0) {
        grid[0][i][remainingMoves] = 1;
      } else if (state[0][i] == 1) {
        remainingMoves++;
        if (remainingMoves > t) {
          remainingMoves--;
        }
        grid[0][i][remainingMoves] = 1;
      } else {
        break;
      }
    }

    for (int i = 1; i <= x; i++) {
      for (int j = 1; j <= y; j++) {
        if (state[i][j] == 0) {
          for (int movesLeft = 0; movesLeft <= t; movesLeft++) {
            grid[i][j][movesLeft] = (grid[i - 1][j][movesLeft] % MOD +
                                     grid[i][j - 1][movesLeft] % MOD) %
                                    MOD;
          }
        } else if (state[i][j] == 1) {
          for (int movesLeft = 0; movesLeft <= t; movesLeft++) {
            grid[i][j][movesLeft] = (grid[i - 1][j][movesLeft] % MOD +
                                     grid[i][j - 1][movesLeft] % MOD) %
                                    MOD;
          }
          if (t > 0) {
            grid[i][j][t - 1] += grid[i][j][t];
            for (int movesLeft = t; movesLeft > 0; movesLeft--) {
              grid[i][j][movesLeft] = grid[i][j][movesLeft - 1];
            }
            grid[i][j][0] = 0;
          }
        }
      }
    }

    fout << grid[x][y][t] << endl;
  }

  fin.close();
  fout.close();

  return 0;
}
