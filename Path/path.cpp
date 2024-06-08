#include <iostream>
#include <fstream>
#include <algorithm>
#define MAX_NODES 100001
#define NEG_INF -1000000001

using namespace std;

int preorder[MAX_NODES], n, node_cost[MAX_NODES], current_idx, max_path_sum;

int findMaxPathSum(int start, int end) {
    if (start == end) {
        max_path_sum = max(max_path_sum, node_cost[start]);
        current_idx++;
        return node_cost[start];
    }
    if (start > end || current_idx == n) return 0;

    int root_pos = start;
    while (root_pos <= end && preorder[current_idx] != root_pos) {
        ++root_pos;
    }
    current_idx++;

    int left_sum = NEG_INF, right_sum = NEG_INF;

    if (root_pos == end) {
        left_sum = findMaxPathSum(start, root_pos - 1);
        return left_sum + node_cost[root_pos];
    } else if (root_pos == start) {
        right_sum = findMaxPathSum(root_pos + 1, end);
        return right_sum + node_cost[root_pos];
    } else {
        left_sum = findMaxPathSum(start, root_pos - 1);
        right_sum = findMaxPathSum(root_pos + 1, end);
        max_path_sum = max(max_path_sum, left_sum + right_sum + node_cost[root_pos]);
        return max(left_sum + node_cost[root_pos], right_sum + node_cost[root_pos]);
    }
}

int main() {
    ifstream fin("path.inp");
    ofstream fout("path.out");

    int T;

    fin >> T;
    while (T--) {
        fin >> n;
        for (int i = 0; i < n; ++i) fin >> node_cost[i];
        for (int i = 0; i < n; ++i) fin >> preorder[i];
        max_path_sum = NEG_INF;
        current_idx = 0;
        findMaxPathSum(0, n - 1);
        fout << max_path_sum << '\n';
    }

    fin.close();
    fout.close();

    return 0;
}
