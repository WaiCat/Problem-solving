#include <fstream>
#include <iostream>
#include <limits>
#include <tuple>

using namespace std;

struct IndexPair {
  int Value;
  int Index;

  IndexPair() : Value(0), Index(0) {}

  IndexPair(int value, int index) : Value(value), Index(index) {}
};

int arr[1000001];
IndexPair tree[2000002];

void build_tree(int node, int start, int end) {
  if (start == end) {
    tree[node] = IndexPair(arr[start], start);
  } else {
    int mid = (start + end) / 2;
    build_tree(2 * node, start, mid);
    build_tree(2 * node + 1, mid + 1, end);
    if (tree[2 * node].Value < tree[2 * node + 1].Value)
      tree[node] = tree[2 * node];
    else if (tree[2 * node].Value > tree[2 * node + 1].Value)
      tree[node] = tree[2 * node + 1];
    else
      tree[node] = (tree[2 * node].Index < tree[2 * node + 1].Index)
                       ? tree[2 * node]
                       : tree[2 * node + 1];
  }
}

IndexPair query_tree(int node, int start, int end, int left, int right) {
  if (start > right || end < left) {
    return {numeric_limits<int>::max(), -1};
  }
  if (left <= start && end <= right) {
    return tree[node];
  }
  int mid = (start + end) / 2;
  IndexPair leftResult = query_tree(2 * node, start, mid, left, right);
  IndexPair rightResult = query_tree(2 * node + 1, mid + 1, end, left, right);
  if (leftResult.Value < rightResult.Value)
    return leftResult;
  else if (leftResult.Value > rightResult.Value)
    return rightResult;
  else
    return {leftResult.Value, min(leftResult.Index, rightResult.Index)};
}

void update_tree(int node, int start, int end, int index, int value) {
  if (start == end) {
    arr[index] = value;
    tree[node] = IndexPair(value, index);
  } else {
    int mid = (start + end) / 2;
    if (index <= mid) {
      update_tree(2 * node, start, mid, index, value);
    } else {
      update_tree(2 * node + 1, mid + 1, end, index, value);
    }
    if (tree[2 * node].Value < tree[2 * node + 1].Value)
      tree[node] = tree[2 * node];
    else if (tree[2 * node].Value > tree[2 * node + 1].Value)
      tree[node] = tree[2 * node + 1];
    else
      tree[node] = (tree[2 * node].Index < tree[2 * node + 1].Index)
                       ? tree[2 * node]
                       : tree[2 * node + 1];
  }
}

int main() {
  ifstream fin("rmq.inp");
  ofstream fout("rmq.out");

  int n;
  fin >> n;

  for (int i = 0; i < n; ++i) {
    fin >> arr[i];
  }

  build_tree(1, 0, n - 1);

  char command;
  int sum = 0;

  while (true) {
    fin >> command;
    if (command == 's') {
      break;
    } else if (command == 'q') {
      int start, end;
      fin >> start >> end;
      IndexPair result = query_tree(1, 0, n - 1, start, end);
      sum = (sum + result.Index) % 100000;
    } else if (command == 'c') {
      int index, value;
      fin >> index >> value;
      update_tree(1, 0, n - 1, index, value);
    }
  }
  fout << sum;

  return 0;
}
