#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

ll minCost(vector<ll>& nums) {
    priority_queue<ll, vector<ll>, greater<ll>> minHeap(nums.begin(), nums.end());
    ll totalCost = 0;
    while (minHeap.size() > 1) {
        ll first = minHeap.top(); minHeap.pop();
        ll second = minHeap.top(); minHeap.pop();
        ll sum = first + second;
        totalCost += sum;
        minHeap.push(sum);
    }
    return totalCost;
}

int main() {
    ifstream fin("add.inp");
    ofstream fout("add.out");

    int n;
    while (fin >> n && n != 0) {
        vector<ll> nums(n);
        for (int i = 0; i < n; ++i) {
            fin >> nums[i];
        }
        ll cost = minCost(nums);
        fout << cost << endl;
    }

    fin.close();
    fout.close();
    return 0;
}
