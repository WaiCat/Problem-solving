#include <fstream>
#include <iostream>

using namespace std;

int main() {
  ifstream fin;
  ofstream fout;
  fin.open("trip.inp");
  fout.open("trip.out");

  int t;
  fin >> t;

  for (int i = 0; i < t; i++) {
    int x, y, a, b, k;
    fin >> x >> y >> a >> b >> k;
  }

  fin.close();
  fout.close();

  return 0;
}
