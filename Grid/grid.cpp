#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

#define MOD 1000000007

using namespace std;

struct Cell {
    int state;
    deque<int> possibilities;

    Cell() : state(0) {}
};

int main() {
    ifstream fin("2.inp");
    ofstream fout("2.txt");

    int test_cases;
    fin >> test_cases;

    for (int t = 0; t < test_cases; ++t) {
        int rows, cols, a, b, k;
        fin >> rows >> cols >> a >> b >> k;

        vector<vector<Cell>> grid(rows + 1, vector<Cell>(cols + 1));

        for (int i = 0; i <= rows; ++i) {
            for (int j = 0; j <= cols; ++j) {
                grid[i][j].possibilities = deque<int>(k + 1, 0);
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

        grid[0][0].possibilities.push_front(1);
        grid[0][0].possibilities.pop_back();

        for (int i = 1; i <= rows; ++i) {
            if (grid[i][0].state == 1) {
                grid[i][0].possibilities = grid[i - 1][0].possibilities;
                grid[i][0].possibilities.push_front(0);
                int carry = grid[i][0].possibilities.back();
                grid[i][0].possibilities.pop_back();
                grid[i][0].possibilities.back() += carry;
            } else if (grid[i][0].state == 0) {
                grid[i][0].possibilities = grid[i - 1][0].possibilities;
            }
        }

        for (int j = 1; j <= cols; ++j) {
            if (grid[0][j].state == 1) {
                grid[0][j].possibilities = grid[0][j - 1].possibilities;
                grid[0][j].possibilities.push_front(0);
                int carry = grid[0][j].possibilities.back();
                grid[0][j].possibilities.pop_back();
                grid[0][j].possibilities.back() += carry;
            } else if (grid[0][j].state == 0) {
                grid[0][j].possibilities = grid[0][j - 1].possibilities;
            }
        }

        for (int i = 1; i <= rows; ++i) {
            for (int j = 1; j <= cols; ++j) {
                if (grid[i][j].state == 0) {
                    deque<int> prev_row = grid[i - 1][j].possibilities;
                    deque<int> prev_col = grid[i][j - 1].possibilities;
                    deque<int> possibilities;
                    for (int l = 0; l < k + 1; ++l) {
                        possibilities.push_back((prev_row[l] % MOD + prev_col[l] % MOD) % MOD);
                    }
                    grid[i][j].possibilities = possibilities;
                } else if (grid[i][j].state == 1) {
                    deque<int> prev_row = grid[i - 1][j].possibilities;
                    deque<int> prev_col = grid[i][j - 1].possibilities;
                    deque<int> possibilities;
                    for (int l = 0; l < k + 1; ++l) {
                        possibilities.push_back((prev_row[l] % MOD + prev_col[l] % MOD) % MOD);
                    }
                    int carry = possibilities.back();
                    possibilities.pop_back();
                    possibilities.back() += carry;
                    possibilities.push_front(0);
                    grid[i][j].possibilities = possibilities;
                }
            }
        }

        fout << grid[rows][cols].possibilities.back() << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
