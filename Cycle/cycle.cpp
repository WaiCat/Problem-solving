#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int countPermutationCycles(const vector<int>& permutation) {
  int n = permutation.size();
  vector<bool> visited(n, false);
  int cycles = 0;

  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      int current = i;
      while (!visited[current]) {
        visited[current] = true;
        current = permutation[current] - 1;
      }
      cycles++;
    }
  }
  return cycles;
}

int main() {
  ifstream fin("cycle.inp");
  ofstream fout("cycle.out");

  int t;
  fin >> t;

  for (int i = 0; i < t; i++) {
    int n;
    fin >> n;
    vector<int> permutation(n);

    for (int j = 0; j < n; j++) {
      fin >> permutation[j];
    }

    int cycles = countPermutationCycles(permutation);
    fout << cycles << endl;
  }

  return 0;
}
