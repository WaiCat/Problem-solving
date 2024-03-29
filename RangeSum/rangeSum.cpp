#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long long A[1000001];
vector<long long> tree;

long long createTree(int start, int end, int idx) {
  if (start == end) return tree[idx] = A[start];

  int mid = (start + end) / 2;
  return tree[idx] = createTree(start, mid, idx * 2) +
                     createTree(mid + 1, end, idx * 2 + 1);
}

long long sum(int start, int end, int left, int right, int idx) {
  if (right < start || left > end) return 0;
  if (left <= start && right >= end) return tree[idx];

  int mid = (start + end) / 2;
  return sum(start, mid, left, right, idx * 2) +
         sum(mid + 1, end, left, right, idx * 2 + 1);
}

void update(int start, int end, int idx, int change, long long dif) {
  if (change < start || change > end) return;

  tree[idx] += dif;

  if (start == end) return;

  int mid = (start + end) / 2;
  update(start, mid, idx * 2, change, dif);
  update(mid + 1, end, idx * 2 + 1, change, dif);
}

int main() {
  ifstream fin("rangeSum.inp");
  ofstream fout("rangeSum.out");

  int n;

  fin >> n;

  for (int i = 1; i <= n; i++) {
    fin >> A[i];
  }

  tree.resize(n * 4);
  createTree(1, n, 1);

  while (true) {
    char command;
    int a, b;
    fin >> command >> a >> b;

    if (command == 'q') {
      break;
    } else if (command == 'c') {
      update(1, n, 1, a, b - A[a]);
      A[a] = b;
    } else {
      fout << sum(1, n, a, b, 1) << "\n";
    }
  }

  return 0;
}