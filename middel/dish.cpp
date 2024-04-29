#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

int building_num;
int left_num;
const int mod = 1000000007;
int dp[101][101];

int main() {

    ifstream fin("dish.inp");
    ofstream fout("dish.out");
    int t;
    fin >> t;
    for (size_t i = 0; i < t; i++)
    {
      fin >> building_num >> left_num;

    memset(dp, 0, sizeof(dp));

    dp[1][1] = 1;

    for (int idx = 2; idx <= building_num; ++idx)
        for (int l = 1; l <= idx; ++l)
            dp[idx][l] = ((long long)dp[idx - 1][l] * (idx - 1) + dp[idx - 1][l - 1]) % mod;

    fout <<building_num << " " << left_num << " "<< dp[building_num][left_num] << '\n';
    }
    return 0;
    
}
