#include <fstream>
#include <iostream>
#include <vector>

#define MOD 1000000007

using namespace std;

struct Cell {
  int state;
  vector<int> possibilities;

  Cell() : state(0) {}
};

int addMod(int a, int b) { return (a % MOD + b % MOD) % MOD; }

int main() {
  ifstream fin("0.inp");
  ofstream fout("0.txt");

  int test_cases;
  fin >> test_cases;

  for (int t = 0; t < test_cases; ++t) {
    int rows, cols, a, b, k;
    fin >> rows >> cols >> a >> b >> k;

    vector<vector<Cell>> grid(rows + 1, vector<Cell>(cols + 1));

    for (int i = 0; i <= rows; ++i) {
      for (int j = 0; j <= cols; ++j) {
        grid[i][j].possibilities = vector<int>(k + 1, 0);
      }
    }

    for (int i = 0; i < a; ++i) {
      int x, y;
      fin >> x >> y;
      grid[x][y].state = 1;
    }

    for (int i = 0; i < b; ++i) {
      int x, y;
      fin >> x >> y;
      grid[x][y].state = 2;
    }

    grid[0][0].possibilities[0] = 1;

    for (int i = 1; i <= rows; ++i) {
      if (grid[i][0].state == 1) {
        grid[i][0].possibilities = grid[i - 1][0].possibilities;
        grid[i][0].possibilities.push_back(0);
        grid[i][0].possibilities.back() = addMod(
            grid[i][0].possibilities.back(),
            grid[i][0].possibilities[grid[i][0].possibilities.size() - 2]);
      } else if (grid[i][0].state == 0) {
        grid[i][0].possibilities = grid[i - 1][0].possibilities;
      }
    }

    for (int j = 1; j <= cols; ++j) {
      if (grid[0][j].state == 1) {
        grid[0][j].possibilities = grid[0][j - 1].possibilities;
        grid[0][j].possibilities.push_back(0);
        grid[0][j].possibilities.back() = addMod(
            grid[0][j].possibilities.back(),
            grid[0][j].possibilities[grid[0][j].possibilities.size() - 2]);
      } else if (grid[0][j].state == 0) {
        grid[0][j].possibilities = grid[0][j - 1].possibilities;
      }
    }

    for (int i = 1; i <= rows; ++i) {
      for (int j = 1; j <= cols; ++j) {
        if (grid[i][j].state == 0) {
          for (int l = 0; l < k + 1; ++l) {
            grid[i][j].possibilities[l] =
                addMod(grid[i - 1][j].possibilities[l],
                       grid[i][j - 1].possibilities[l]);
          }
        } else if (grid[i][j].state == 1) {
          for (int l = 0; l < k + 1; ++l) {
            grid[i][j].possibilities[l] =
                addMod(grid[i - 1][j].possibilities[l],
                       grid[i][j - 1].possibilities[l]);
          }
          grid[i][j].possibilities.push_back(0);
          grid[i][j].possibilities.back() = addMod(
              grid[i][j].possibilities.back(),
              grid[i][j].possibilities[grid[i][j].possibilities.size() - 2]);
        }
      }
    }

    fout << grid[rows][cols].possibilities.back() << endl;
  }

  fin.close();
  fout.close();

  return 0;
}
