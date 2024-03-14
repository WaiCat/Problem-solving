#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
https://blog.ugonfor.kr/52
int main() {
    ifstream inFile("1.txt"); // 입력 파일 열기
    ofstream outFile("output.txt"); // 출력 파일 열기

    int i, j;
    inFile >> i >> j; // 파일에서 입력 받기
xxxxx`
    outFile << i << " " << j << " "; // 파일에 출력

    int count = 0;
    for (; i <= j; i++) {
        int n = i;
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

    outFile << count + 1; // 파일에 출력
    inFile.close(); // 파일 닫기
    outFile.close(); // 파일 닫기

    return 0;
}
