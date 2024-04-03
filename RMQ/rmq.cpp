#include <fstream>
#include <iostream>
#include <limits>
#include <tuple>

using namespace std;

int arr[100];
int tree[100];

struct IndexPair {
  int Value;
  int Index;
};

void build_tree(int node, int start, int end) {
  if (start == end) {
    tree[node] = start;
  } else {
    int mid = (start + end) / 2;
    build_tree(2 * node, start, mid);
    build_tree(2 * node + 1, mid + 1, end);
    if (arr[tree[2 * node]] < arr[tree[2 * node + 1]])
      tree[node] = tree[2 * node];
    else if (arr[tree[2 * node]] > arr[tree[2 * node + 1]])
      tree[node] = tree[2 * node + 1];
    else
      tree[node] = min(tree[2 * node], tree[2 * node + 1]);
  }
}

IndexPair query_tree(int node, int start, int end, int left, int right) {
  if (start > right || end < left) {
    return {numeric_limits<int>::max(), -1};
  }
  if (left <= start && end <= right) {
    return {arr[tree[node]], tree[node]};
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
    tree[node] = index;
  } else {
    int mid = (start + end) / 2;
    if (index <= mid) {
      update_tree(2 * node, start, mid, index, value);
    } else {
      update_tree(2 * node + 1, mid + 1, end, index, value);
    }
    if (arr[tree[2 * node]] < arr[tree[2 * node + 1]])
      tree[node] = tree[2 * node];
    else if (arr[tree[2 * node]] > arr[tree[2 * node + 1]])
      tree[node] = tree[2 * node + 1];
    else
      tree[node] = min(tree[2 * node], tree[2 * node + 1]);
  }
}

int main() {
  ifstream fin("0.inp");
  ofstream fout("0.txt");

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
