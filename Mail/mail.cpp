#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, char> codeMap = {
    {"000000", 'A'}, {"001111", 'B'}, {"010011", 'C'}, {"011100", 'D'},
    {"100110", 'E'}, {"101001", 'F'}, {"110101", 'G'}, {"111010", 'H'}};

// 비밀편지를 해독하는 함수
char decodeLetter(const string& code) {
  for (const auto& p : codeMap) {
    int diffCount = 0;
    for (int i = 0; i < 6; i++) {
      if (code[i] != p.first[i]) {
        diffCount++;
      }
    }
    if (diffCount == 0) return p.second;
    if (diffCount == 1) return p.second;
  }
  return 'X';
}

int main() {
  ifstream fin("mail.inp");
  ofstream fout("mail.out");

  int T;
  fin >> T;  // 테스트 케이스의 수

  while (T--) {
    int N;
    fin >> N;  // 문자의 개수
    string sequence;
    fin >> sequence;

    string result = "";

    for (int i = 0; i < N; i++) {
      string currentCode = sequence.substr(i * 6, 6);
      result += decodeLetter(currentCode);
    }

    fout << result << endl;
  }

  fin.close();
  fout.close();

  return 0;
}
