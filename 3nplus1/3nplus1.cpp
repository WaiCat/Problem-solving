#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
    ifstream fin; ofstream fout;
    fin.open("1.inp"); fout.open("3nplus1.out");

    int i, j;

    while(fin >> i >> j){
        fout << i << " " << j << " "; 

        int minn = i < j ? i : j;
        int maxn = i > j ? i : j;

        int count = 0;
        for (; minn <= maxn; minn++) {
            int n = minn;
            int tmp = 0;
            while (n != 1) {
                tmp++;
                if (n % 2 == 0) {
                    n = n / 2;
                } else {
                    n = 3 * n + 1;
                }
            }
            count = max(count, tmp);
        }
        fout << count + 1 << endl;
    }

    fin.close();
    fout.close(); 

    return 0;
}
