#include <iostream>
#include <sstream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string input;
    getline(cin, input);
    stringstream ss(input);
    
    int i, j;
    ss >> i >> j;
    
    cout << i << " " << j << " ";
    
    int count = 0;
    for (; i <= j; ++i) {
        int n = i;
        int tmp = 0;
        while (n != 1) {
            ++tmp;
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
        }
        count = max(count, tmp);
    }
    
    cout << count + 1 << "\n";
    
    return 0;
}
