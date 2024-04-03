#include <math.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;
#define INF 1000000000  // 10��

pair<int, int> init(int node, int s, int e, pair<int, int>* seg, int* arr) {
  if (s == e)
    return seg[node] = {
               arr[s],
               s};  // start �� end �� ��ġ�� ��ġ�ϸ� input[start] ���� �־��ش�.
  int mid = (s + e) / 2;
  return seg[node] = min(
             init(2 * node, s, mid, seg, arr),
             init(2 * node + 1, mid + 1, e, seg, arr));  // �ٸ� ������ ������
}

pair<int, int> query(int node, int s, int e, int l, int r,
                     pair<int, int>* seg) {
  if (e < l || r < s)
    return {INF, INF};  // ã�ƾ��ϴ� ������ ��屸���� ��ġ�� ���� ��
  if (l <= s && e <= r) return seg[node];  // ã�ƾ��ϴ� �������� ��屸���� ���Ե� ��
  int mid = (s + e) / 2;
  // ã�ƾ��ϴ� ������ ��屸���� ���Եǰų�, �κ������� ��ġ�� ���
  return min(query(2 * node, s, mid, l, r, seg),
             query(2 * node + 1, mid + 1, e, l, r, seg));
}

void update(int node, int s, int e, int idx, int val, pair<int, int>* seg,
            int* arr) {
  if (s == e && s == idx) {  // leaf ��忡 �������� ��
    seg[node] = {val, idx};  // ���׸�Ʈ Ʈ�� ������Ʈ
    return;
  }

  int mid = (s + e) / 2;
  if (idx <= mid) {  // ���� �ڽ� ��忡 ���ԵǴ� ���
    update(2 * node, s, mid, idx, val, seg, arr);
  } else {  // ������ �ڽ� ��忡 ���ԵǴ� ���
    update(2 * node + 1, mid + 1, e, idx, val, seg, arr);
  }

  // �θ� ��� ������Ʈ
  seg[node] = min(seg[2 * node], seg[2 * node + 1]);
}

int findIndex(int arr[], int size, int value) {
  for (int i = 0; i < size; ++i) {
    if (arr[i] == value) {
      return i;  // ���� �߰ߵǸ� �ش� �ε����� ��ȯ
    }
  }
  return -1;  // ���� ã�� ���� ��� -1�� ��ȯ
}

int main() {
  ifstream fin;
  ofstream fout;

  fin.open("0.inp");
  fout.open("0.txt");
  int n, a, b, tmp;
  int answer = 0;
  string command;

  fin >> n;
  int* arr = new int[n];
  pair<int, int>* seg = new pair<int, int>[n * 4];
  for (int i = 0; i < n; i++) {
    fin >> tmp;
    arr[i] = tmp;
  }

  init(1, 0, n - 1, seg, arr);  // ���׸�Ʈ Ʈ�� �����
  // for (int i = 0; i < n*4; i++) {
  //	cout << seg[i] << " ";
  // }

  while (true) {
    fin >> command >> a >> b;

    if (command == "s") break;
    if (command == "q") {
      pair<int, int> result = query(1, 0, n - 1, a, b, seg);
      answer = (answer + result.second) % 100000;
      // cout << command << " " << a << " " << b << " " << result.second <<
      // endl; answer += findIndex(arr, n, result);
    }
    if (command == "c") {
      arr[a] = b;
      // ���׸�Ʈ Ʈ��(seg �迭) ������Ʈ
      update(1, 0, n - 1, a, b, seg, arr);
      // init(1, 0, n-1, seg, arr); // ���׸�Ʈ Ʈ�� �����
    }
  }
  fout << answer;
}