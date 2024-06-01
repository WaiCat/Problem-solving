#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

// 입력 문자열을 받아서 파싱하는 함수 정의
void parseInput(string inputStr, string &value1, char &operand, string &value2) {
    istringstream iss(inputStr);

    // 공백을 기준으로 문자열을 읽어와서 처리
    iss >> value1; // 첫 번째 값 읽기

    // '.'(점) 이전의 0 삭제
    size_t dotPosition = value1.find('.');
    if (dotPosition != string::npos) {
        // '.' 이전의 0 찾기
        size_t nonZeroPosition = value1.find_first_not_of('0');
        if (nonZeroPosition != string::npos && nonZeroPosition < dotPosition) {
            // '.' 이전의 0이 아닌 숫자가 나올 때까지의 위치 반환
            value1.erase(0, nonZeroPosition);
        }
    }

    iss >> operand; // 연산자 읽기
    iss >> value2; // 두 번째 값 읽기
}

int main() {
    ifstream fin("1.inp"); // 입력 파일 읽기
    ofstream fout("1.txt"); // 출력 파일 쓰기

    int T;
    fin >> T;

    string inputStr;
    while (T--) {
        fin.ignore(); // 버퍼 비우기
        getline(fin, inputStr); // 한 줄씩 입력 받기

        string value1, value2;
        char operand;

        // 입력 문자열 파싱
        parseInput(inputStr, value1, operand, value2);

        // 문자열을 정수로 변환
        int intValue1 = stoi(value1);

        // 파싱된 결과 출력
        fout << intValue1 << operand << value2 << endl;
    }

    fin.close(); // 파일 닫기
    fout.close(); // 파일 닫기

    return 0;
}
