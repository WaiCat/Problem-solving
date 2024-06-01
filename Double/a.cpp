#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

int nonZeroPosition;
int dotPosition;

// 입력 문자열을 받아서 파싱하는 함수 정의
void parseInput(string inputStr, string &value1, char &operand, string &value2) {
    istringstream iss(inputStr);

    // 공백을 기준으로 문자열을 읽어와서 처리
    iss >> value1; // 첫 번째 값 읽기
    iss >> operand; // 연산자 읽기
    iss >> value2; // 두 번째 값 읽기

    int l = value1.length()-1;
    int v1dotPosition = value1.find('.');
    if (v1dotPosition != string::npos) {
        value1.erase(v1dotPosition, 1); // '.'(점) 삭제
        v1dotPosition = l - v1dotPosition;
    }

    l = value2.length()-1;
    int v2dotPosition = value2.find('.');
    if (v2dotPosition != string::npos) {
        value2.erase(v2dotPosition, 1); // '.'(점) 삭제
        v2dotPosition = l - v2dotPosition;
    }

    // value1과 value2의 소수점 위치의 차이를 계산합니다.
    int dotPositionDiff = v1dotPosition - v2dotPosition;

    if (dotPositionDiff > 0) {
        // value2 뒤에 0을 추가하여 소수점 위치를 맞춥니다.
        value2.append(dotPositionDiff, '0');
    }
    // value2의 소수점이 더 앞에 있는 경우
    else if (dotPositionDiff < 0) {
        // value1 뒤에 0을 추가하여 소수점 위치를 맞춥니다.
        value1.append(-dotPositionDiff, '0');
    }
}

// 덧셈 연산 함수 정의
string addition(string value1, string value2) {
    // value1과 value2를 더합니다.
    string result;
    int carry = 0;
    int i = value1.size() - 1;
    int j = value2.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += value1[i--] - '0';
        if (j >= 0) sum += value2[j--] - '0';
        result.insert(result.begin(), sum % 10 + '0');
        carry = sum / 10;
    }
    return result;
}

// 뺄셈 연산 함수 정의
string subtraction(string value1, string value2) {
    // value1에서 value2를 뺍니다.
    string result;
    int borrow = 0;
    int i = value1.size() - 1;
    int j = value2.size() - 1;
    while (i >= 0 || j >= 0) {
        int diff = (i >= 0 ? value1[i--] - '0' : 0) - borrow - (j >= 0 ? value2[j--] - '0' : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.insert(result.begin(), diff + '0');
    }
    return result;
}

// 곱셈 연산 함수 정의
string multiplication(string value1, string value2) {
    // value1과 value2를 곱합니다.
    string result = "0";
    for (int i = value2.size() - 1; i >= 0; i--) {
        string temp = value1;
        int carry = 0;
        for (int j = temp.size() - 1; j >= 0; j--) {
            int prod = (temp[j] - '0') * (value2[i] - '0') + carry;
            carry = prod / 10;
            temp[j] = prod % 10 + '0';
        }
        if (carry > 0) {
            temp.insert(temp.begin(), carry + '0');
        }
        temp.append(value2.size() - i - 1, '0');
        result = addition(result, temp);
    }
    return result;
}

// 나눗셈 연산 함수 정의
string division(string value1, string value2) {
    // value1을 value2로 나눈 몫을 구합니다.
    string result;
    string quotient;
    string remainder = value1;
    while (remainder.size() > value2.size() || (remainder.size() == value2.size() && remainder >= value2)) {
        string temp = value2;
        string temp_quotient = "1";
        while (temp.size() < remainder.size() || (temp.size() == remainder.size() && temp <= remainder)) {
            temp += '0';
            temp_quotient += '0';
        }
        temp.pop_back();
        temp_quotient.pop_back();
        remainder = subtraction(remainder, temp);
        quotient = addition(quotient, temp_quotient);
    }
    result = quotient;
    return result;
}

int main() {
    ifstream fin("1.inp"); // 입력 파일 읽기
    ofstream fout("1.txt"); // 출력 파일 쓰기

    int T;
    fin >> T;

    string inputStr;
    getline(fin, inputStr); // 한 줄씩 입력 받기
    while (T--) {
        getline(fin, inputStr); // 한 줄씩 입력 받기

        string value1, value2;
        char operand;

        // 입력 문자열 파싱
        parseInput(inputStr, value1, operand, value2);

        // 파싱된 결과 출력
        if (operand == '+') {
            // 덧셈 연산인 경우
            fout << addition(value1, value2) << endl;
        } else if (operand == '-') {
            // 뺄셈 연산인 경우
            fout << subtraction(value1, value2) << endl;
        } else if (operand == '*') {
            // 곱셈 연산인 경우
            fout << multiplication(value1, value2) << endl;
        } else if (operand == '/') {
            // 나눗셈 연산인 경우
            fout << division(value1, value2) << endl;
        }
    }

    fin.close(); // 파일 닫기
    fout.close(); // 출력 파일 닫기

    return 0;
}
