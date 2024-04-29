#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;


int main() {
  ifstream fin("multi4.inp");
  ofstream fout("multi4.out");

  int t;
  fin >>t;

  for (int i = 0; i < t; i++) {
      int n;
      fin >> n;

      vector<int> v;
      for (size_t j = 0; j < n; j++)
      {
          int a;
          fin >> a;
          v.push_back(a);
      }
      sort(v.begin(), v.end());
      long long a, b, c, d, e;
      int l = v.size();

    a= v[0] * v[1] * v[2] * v[3];
    b = v[0] * v[1] * v[2] * v[3];

      for (int i = 0; i <= l; i++)
      {
          c = v[i % l] * v[(i + 1) % l] * v[(i + 2) % l] * v[(i + 3) % l];
          a = min(a, c);
          b = max(b, c);
      }

      fout << a << " " << b << endl;

      //   a = v[0] * v[1] * v[2] * v[l - 1];
      //   b = v[l - 1] * v[l - 2] * v[l - 3] * v[0];
      //   c = v[0] * v[1] * v[2] * v[3];
      //   d = v[l - 1] * v[l - 2] * v[l - 3] * v[l - 4];
      //   e = v[0] * v[1] * v[l - 1] * v[l - 2];

      //   fout << min({a, b, c, d, e}) << " ";

      //   a = v[0] * v[1] * v[2] * v[3];
      //   b = v[l - 1] * v[l - 2] * v[l - 3] * v[l - 4];
      //   c = v[0] * v[1] * v[l - 1] * v[l - 2];
      //   fout << max(max(a, b), c)<<endl;
  }

return 0;
}