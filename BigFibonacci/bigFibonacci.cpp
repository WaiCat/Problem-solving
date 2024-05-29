#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

vector<vector<long long>> matrixMultiply(const vector<vector<long long>> &a, const vector<vector<long long>> &b) {
    vector<vector<long long>> result(2, vector<long long>(2));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return result;
}

vector<vector<long long>> matrixPower(vector<vector<long long>> base, long long exp) {
    vector<vector<long long>> result = {{1, 0}, {0, 1}}; // 단위 행렬
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = matrixMultiply(result, base);
        }
        base = matrixMultiply(base, base);
        exp /= 2;
    }
    return result;
}

long long fibonacci(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    vector<vector<long long>> F = {{1, 1}, {1, 0}};
    F = matrixPower(F, n - 1);
    return F[0][0];
}

int main() {
    ifstream fin("bigFibonacci.inp");
    ofstream fout("bigFibonacci.out");

    int T;
    fin >> T;
    vector<long long> testCases(T);
    for (int i = 0; i < T; ++i) {
        fin >> testCases[i];
    }

    for (int i = 0; i < T; ++i) {
        long long n = testCases[i];
        long long fn = fibonacci(n);
        fout << n << " " << fn << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
