#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>

using namespace std;

// Node structure
struct Node {
    int key;
    Node *left, *right;
    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

// Function to build tree from preorder traversal and keys
Node* buildTree(vector<int>& keys, vector<int>& preorder, int& preIndex, int inStart, int inEnd, vector<int>& inorderIndex) {
    if (inStart > inEnd) return nullptr;
    
    int rootKey = preorder[preIndex++];
    Node* root = new Node(keys[rootKey]);
    
    if (inStart == inEnd) return root;
    
    int inIndex = inorderIndex[rootKey];
    
    root->left = buildTree(keys, preorder, preIndex, inStart, inIndex - 1, inorderIndex);
    root->right = buildTree(keys, preorder, preIndex, inIndex + 1, inEnd, inorderIndex);
    
    return root;
}

// Helper function to find the maximum path sum between any two leaves
int maxPathSumUtil(Node* root, int& maxSum) {
    if (!root) return 0;
    
    int leftSum = maxPathSumUtil(root->left, maxSum);
    int rightSum = maxPathSumUtil(root->right, maxSum);
    
    if (root->left && root->right) {
        maxSum = max(maxSum, leftSum + rightSum + root->key);
        return max(leftSum, rightSum) + root->key;
    }
    
    return (root->left ? leftSum : rightSum) + root->key;
}

// Function to find the maximum path sum between any two leaf nodes
int findMaxPathSum(Node* root) {
    int maxSum = INT_MIN;
    maxPathSumUtil(root, maxSum);
    return maxSum;
}

int main() {
    ifstream inputFile("2.inp");
    ofstream outputFile("2.txt");
    
    int T;
    inputFile >> T;
    while (T--) {
        int n;
        inputFile >> n;
        
        vector<int> keys(n);
        for (int i = 0; i < n; ++i) {
            inputFile >> keys[i];
        }
        
        vector<int> preorder(n);
        for (int i = 0; i < n; ++i) {
            inputFile >> preorder[i];
        }
        
        vector<int> inorderIndex(n);
        for (int i = 0; i < n; ++i) {
            inorderIndex[i] = i;
        }
        
        int preIndex = 0;
        Node* root = buildTree(keys, preorder, preIndex, 0, n - 1, inorderIndex);
        
        outputFile << findMaxPathSum(root) << endl;
    }
    
    inputFile.close();
    outputFile.close();
    
    return 0;
}
