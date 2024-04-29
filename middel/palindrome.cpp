#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int rev(int n) {
	string s = to_string(n);
	reverse(s.begin(), s.end());
	return atoi(s.c_str());
}

int main() {
  ifstream fin("palindrome.inp");
  ofstream fout("palindrome.out");

  int t;
  fin >> t;

  for (int i = 0; i < t; i++) {
      int n;
      fin >> n;

      int nr = rev(n);

      int index = 0;
      while(nr != n){
          index++;
          n = abs(n - nr);
          nr = rev(n);
          if(index > 999){
              index = -1;
              break;
          }
      }
      fout << index << endl;
  }

return 0;
}