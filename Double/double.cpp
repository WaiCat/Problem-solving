#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int v1dotPosition, v2dotPosition;

class BigInt {
private:
    string value;
    bool isNegative;

    static void addLeadingZeros(string &num, int zeros) {
        num.insert(0, zeros, '0');
    }

    static string addStrings(const string &num1, const string &num2) {
        string result;
        int carry = 0, sum = 0;
        int n1 = num1.size(), n2 = num2.size();

        for (int i = 0; i < max(n1, n2) || carry; ++i) {
            if (i < n1) sum += num1[n1 - 1 - i] - '0';
            if (i < n2) sum += num2[n2 - 1 - i] - '0';
            sum += carry;
            result.push_back(sum % 10 + '0');
            carry = sum / 10;
            sum = 0;
        }

        reverse(result.begin(), result.end());
        return result;
    }

    static string subtractStrings(const string &num1, const string &num2) {
        string result;
        int borrow = 0, diff = 0;
        int n1 = num1.size(), n2 = num2.size();

        for (int i = 0; i < n1; ++i) {
            diff = (num1[n1 - 1 - i] - '0') - (i < n2 ? (num2[n2 - 1 - i] - '0') : 0) - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(diff + '0');
        }

        while (result.size() > 1 && result.back() == '0') result.pop_back();

        reverse(result.begin(), result.end());
        return result;
    }

    static string multiplyStrings(const string &num1, const string &num2) {
        int n1 = num1.size(), n2 = num2.size();
        vector<int> result(n1 + n2, 0);

        for (int i = n1 - 1; i >= 0; --i) {
            for (int j = n2 - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + result[i + j + 1];
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }

        string resultStr;
        for (int num : result) if (!(resultStr.empty() && num == 0)) resultStr.push_back(num + '0');

        return resultStr.empty() ? "0" : resultStr;
    }

    static string divideStrings(const string &num1, const string &num2) {
        string result;
        string current;

        int index = num1.find_first_not_of('0');
        if (index == string::npos)
          index = 0;
        string modified_num1 = num1.substr(index, num1.length());
        
        index = num2.find_first_not_of('0');
        if (index == string::npos)
          index = 0;
        string modified_num2 = num2.substr(index, num2.length());

        int l = modified_num2.size();

        for (char digit : modified_num1) {
            current += digit;
            int x = 0;

            while (current.size() > 1 && current[0] == '0') current.erase(0, 1);
            while (current.size() >= modified_num2.size()) {
                if (current.size() > modified_num2.size() || current >= modified_num2) {
                    current = subtractStrings(current, modified_num2);
                    x++;
                } else {
                    break;
                }
            }
            result.push_back(x + '0');
        }

        while (result.size() > 1 && result[0] == '0') result.erase(0, 1);

        return result.empty() ? "0" : result;
    }

public:
    BigInt() : value("0"), isNegative(false) {}

    BigInt(string val) : value(move(val)), isNegative(false) {
        if (value.empty()) value = "0";
        else if (value[0] == '-') {
            isNegative = true;
            value.erase(0, 1);
        }
    }

    BigInt operator+(const BigInt &other) const {
        if (isNegative == other.isNegative) {
            BigInt result(addStrings(value, other.value));
            result.isNegative = isNegative;
            return result;
        } else {
            if (isNegative) {
                BigInt temp(value);
                temp.isNegative = false;
                return other - temp;
            } else {
                BigInt temp(other.value);
                temp.isNegative = false;
                return *this - temp;
            }
        }
    }

    BigInt operator-(const BigInt &other) const {
        if (isNegative == other.isNegative) {
            if (*this < other) {
                BigInt result(subtractStrings(other.value, value));
                result.isNegative = !isNegative;
                return result;
            } else {
                BigInt result(subtractStrings(value, other.value));
                result.isNegative = isNegative;
                return result;
            }
        } else {
            BigInt temp(other.value);
            temp.isNegative = !other.isNegative;
            return *this + temp;
        }
    }

    BigInt operator*(const BigInt &other) const {
        BigInt result(multiplyStrings(value, other.value));
        result.isNegative = isNegative != other.isNegative;
        return result;
    }

    BigInt operator/(const BigInt &other) const {
        BigInt result(divideStrings(value, other.value));
        result.isNegative = isNegative != other.isNegative;
        return result;
    }

    bool operator<(const BigInt &other) const {
        if (isNegative != other.isNegative) return isNegative;
        if (value.size() != other.value.size()) return value.size() < other.value.size();
        return value < other.value;
    }

    string toString() const {
        return (isNegative ? "-" : "") + value;
    }
};

// 입력 문자열을 받아서 파싱하는 함수 정의
void parseInput(string inputStr, string &value1, char &operand, string &value2) {
    istringstream iss(inputStr);
    iss >> value1; // 첫 번째 값 읽기
    iss >> operand; // 연산자 읽기
    iss >> value2; // 두 번째 값 읽기

    int l1 = value1.length();
    v1dotPosition = value1.find('.');
    if (v1dotPosition != string::npos) {
        value1.erase(v1dotPosition, 1); // '.'(점) 삭제
        v1dotPosition = l1 - v1dotPosition - 1;
    }else{
        v1dotPosition = 0;
    }

    int l2 = value2.length();
    v2dotPosition = value2.find('.');
    if (v2dotPosition != string::npos) {
        value2.erase(v2dotPosition, 1); // '.'(점) 삭제
        v2dotPosition = l2 - v2dotPosition - 1;
    }else{
        v2dotPosition = 0;
    }

    int dotPositionDiff = v1dotPosition - v2dotPosition;
    if (dotPositionDiff > 0) {
        value2.append(dotPositionDiff, '0');
    } else if (dotPositionDiff < 0) {
        value1.append(-dotPositionDiff, '0');
    }
}

string insertDecimal(string str, int n) {
    if(n>0){
        int l = str.size();
        int dotPosition = str.size() - n;

        if (str[0] == '-') {
            if (dotPosition < 1){
                dotPosition *= -1;
                str.insert(1, dotPosition + 1, '0');
                dotPosition = str.size() - n;
            }
            if(dotPosition == 1){
                str.insert(dotPosition, "0.");
            }
            else{
                    str.insert(dotPosition, ".");
            }
        }else{
            if (dotPosition < 0) {
                dotPosition *= -1;
                str.insert(0, dotPosition, '0');
                dotPosition = str.size() - n;
            }
            if(dotPosition == 0){
                str.insert(dotPosition, "0.");
            }
            else{ 
                    str.insert(str.size() - n, ".");
            }
        }
    }

    size_t lastNonZero = str.find_last_not_of('0');
    

    if (lastNonZero == string::npos) {
        return str;
    }

    str = str.substr(0, lastNonZero + 1);

     if (str[str.length()-1] == '.') {
        str.erase(lastNonZero);
    }

    if (str == "-0") {
       str = "0";
    }
    return str;
}


// 덧셈 함수 정의
string addition(string value1, string value2) {
    BigInt num1(value1);
    BigInt num2(value2);
    BigInt result = num1 + num2;
    string resultStr = result.toString();

    resultStr = insertDecimal(resultStr, max(v1dotPosition, v2dotPosition));

    return resultStr;
}

// 뺄셈 함수 정의
string subtraction(string value1, string value2) {
    BigInt num1(value1);
    BigInt num2(value2);
    BigInt result = num1 - num2;
    string resultStr = result.toString();

    resultStr = insertDecimal(resultStr, max(v1dotPosition, v2dotPosition));
    
    return resultStr;
}

// 곱셈 함수 정의
string multiplication(string value1, string value2) {
    BigInt num1(value1);
    BigInt num2(value2);
    BigInt result = num1 * num2;
    string resultStr = result.toString();

    resultStr = insertDecimal(resultStr, max(v1dotPosition, v2dotPosition) * 2);
    
    return resultStr;
}

// 나눗셈 함수 정의
string division(string value1, string value2) {
    BigInt num1(value1);
    BigInt num2(value2);
    BigInt result = num1 / num2;
    string resultStr = result.toString();

    if (resultStr == "-0") {
       resultStr = "0";
    }

    return resultStr;
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
            fout << addition(value1, value2) << endl;
        } else if (operand == '-') {
            fout << subtraction(value1, value2) << endl;
        } else if (operand == '*') {
            fout << multiplication(value1, value2) << endl;
        } else if (operand == '/') {
            fout << division(value1, value2) << endl;
        }
    }

    fin.close(); // 파일 닫기
    fout.close(); // 파일 닫기

    return 0;
}
