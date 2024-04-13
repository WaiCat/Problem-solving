#include <fstream>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;

tuple<long long, long long, long long> extended_gcd(long long a, long long b) {
  if (b == 0) return make_tuple(a, 1, 0);
  long long d, x, y;
  tie(d, x, y) = extended_gcd(b, a % b);
  return make_tuple(d, y, x - (a / b) * y);
}

tuple<bool, long long, long long> solve_crt(long long a1, long long n1,
                                            long long a2, long long n2) {
  long long d, x, y;
  tie(d, x, y) = extended_gcd(n1, n2);

  if ((a2 - a1) % d != 0) return make_tuple(false, 0, 0);

  long long n1d = n1 / d, n2d = n2 / d;
  long long x0 = (a2 - a1) / d * x % n2d;
  long long lcm = n1 * n2d;

  long long result = (x0 * n1 + a1) % lcm;
  if (result < 0) result += lcm;
  return make_tuple(true, result, lcm);
}

long long solve_modular_system(const vector<long long>& r,
                               const vector<long long>& m) {
  long long x = r[0], mod = m[0];

  for (size_t i = 1; i < r.size(); ++i) {
    bool exists;
    long long new_x, new_mod;
    tie(exists, new_x, new_mod) = solve_crt(x, mod, r[i], m[i]);
    if (!exists) return -1;
    x = new_x;
    mod = new_mod;
  }

  return x;
}

int main() {
  ifstream fin("crt.inp");
  ofstream fout("crt.out");

  int t;
  fin >> t;
  while (t--) {
    int k;
    fin >> k;

    vector<long long> r, m;
    for (int j = 0; j < k; j++) {
      long long q, w;
      fin >> q >> w;
      r.push_back(q);
      m.push_back(w);
    }

    long long x = solve_modular_system(r, m);
    fout << x << endl;
  }

  return 0;
}
