#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

int arr[1000001];
int tree[2000001];

void build_tree(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;
        build_tree(2 * node, start, mid);
        build_tree(2 * node + 1, mid + 1, end);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
}

void update_tree(int node, int start, int end, int index, int value) {
    if (start == end) {
        arr[index] = value;
        tree[node] = value;
    } else {
        int mid = (start + end) / 2;
        if (index <= mid) {
            update_tree(2 * node, start, mid, index, value);
        } else {
            update_tree(2 * node + 1, mid + 1, end, index, value);
        }
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
}

int query_tree(int node, int start, int end, int left, int right) {
    if (start > right || end < left) {
        return numeric_limits<int>::max();
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    int mid = (start + end) / 2;
    return min(query_tree(2 * node, start, mid, left, right),
               query_tree(2 * node + 1, mid + 1, end, left, right));
}

int main() {
    ifstream fin("1.inp");
    ofstream fout("1.txt");

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
            sum += query_tree(1, 0, n - 1, start - 1, end - 1);
        } else if (command == 'c') {
            int index, value;
            fin >> index >> value;
            update_tree(1, 0, n - 1, index - 1, value);
        }
    }
    fout << sum;

    return 0;
}
