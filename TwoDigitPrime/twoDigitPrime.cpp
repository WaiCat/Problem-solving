#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

bool isPrime(int n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) return false;
  }
  return true;
}

bool hasTwoDigitPrimeCombination(int num) {
  string numStr = to_string(num);
  unordered_set<int> checkedCombinations;

  for (size_t i = 0; i < numStr.size(); ++i) {
    for (size_t j = i + 1; j < numStr.size(); ++j) {
      int combination1 = (numStr[i] - '0') * 10 + (numStr[j] - '0');
      int combination2 = (numStr[j] - '0') * 10 + (numStr[i] - '0');

      if (combination1 >= 10 && combination1 < 100 &&
          checkedCombinations.find(combination1) == checkedCombinations.end()) {
        if (isPrime(combination1)) return true;
        checkedCombinations.insert(combination1);
      }

      if (combination2 >= 10 && combination2 < 100 &&
          checkedCombinations.find(combination2) == checkedCombinations.end()) {
        if (isPrime(combination2)) return true;
        checkedCombinations.insert(combination2);
      }
    }
  }

  return false;
}

int main() {
  ifstream fin("twoDigitPrime.inp");
  ofstream fout("twoDigitPrime.out");

  int T;
  fin >> T;

  while (T--) {
    int A, B;
    fin >> A >> B;

    int count = 0;
    for (int num = A; num <= B; ++num) {
      if (hasTwoDigitPrimeCombination(num)) {
        ++count;
      }
    }

    fout << count << endl;
  }

  fin.close();
  fout.close();

  return 0;
}
