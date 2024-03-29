#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("dish.inp");
  ofstream fout("dish.out");

  int t1;

  fin >> t1;

  for (int i = 0; i < t1; i++) {
    int t2;
    fin >> t2;
    char dish, prev;
    fin >> prev;
    int high = 10;
    for (int j = 1; j < t2; j++) {
      fin >> dish;
      if (prev == dish) {
        high += 5;
      } else {
        high += 10;
      }
      prev = dish;
    }
    fout << high << endl;
  }

  fin.close();
  fout.close();

  return 0;
}
