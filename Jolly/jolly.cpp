#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool isJollyJumper(const vector<int>& sequence) {
  int n = sequence.size();
  vector<bool> diff(n - 1, false);

  for (int i = 0; i < n - 1; ++i) {
    int absoluteDiff = abs(sequence[i] - sequence[i + 1]);
    if (absoluteDiff >= 1 && absoluteDiff <= n - 1) {
      diff[absoluteDiff - 1] = true;
    }
  }

  return all_of(diff.begin(), diff.end(), [](bool val) { return val; });
}

int main() {
  ifstream fin("jolly.inp");
  ofstream fout("jolly.out");

  int n;

  while (fin >> n) {
    vector<int> sequence(n);
    for (int i = 0; i < n; ++i) {
      fin >> sequence[i];
    }

    if (isJollyJumper(sequence)) {
      fout << "Jolly" << endl;
    } else {
      fout << "Not Jolly" << endl;
    }
  }

  return 0;
}
