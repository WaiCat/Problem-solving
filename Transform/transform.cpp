#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// 이진 트리 노드 구조체
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 주어진 inorder 순회 결과로부터 이진 트리를 구성하는 함수
TreeNode* buildTree(vector<int>& inorder) {
    stack<TreeNode*> s;
    TreeNode* root = nullptr;

    for (int val : inorder) {
        TreeNode* node = new TreeNode(val);

        if (s.empty()) {
            root = node;
        } else {
            if (val < s.top()->val) {
                s.top()->left = node;
            } else {
                TreeNode* parent = nullptr;
                while (!s.empty() && val > s.top()->val) {
                    parent = s.top();
                    s.pop();
                }
                parent->right = node;
            }
        }

        s.push(node);
    }

    return root;
}

// 이진 트리를 inorder로 순회하여 결과를 반환하는 함수
void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;

    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

// 이진 트리를 preorder로 순회하여 결과를 반환하는 함수
void preorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;

    result.push_back(root->val);
    preorderTraversal(root->left, result);
    preorderTraversal(root->right, result);
}

// 이진 트리를 괄호식으로 변환하는 함수
string treeToParenthesis(TreeNode* root) {
    if (!root) return "";

    string left = treeToParenthesis(root->left);
    string right = treeToParenthesis(root->right);

    return "(" + left + ")" + "(" + right + ")";
}

// 괄호식을 이진 트리로 변환하는 함수
TreeNode* parenthesisToTree(string& s) {
    stack<TreeNode*> st;
    for (char c : s) {
        if (c == '(') {
            st.push(nullptr);
        } else if (c == ')') {
            TreeNode* right = st.top();
            st.pop();
            TreeNode* left = st.top();
            st.pop();
            TreeNode* node = new TreeNode(0);
            node->left = left;
            node->right = right;
            st.push(node);
        }
    }
    return st.top();
}

int main() {
    ifstream fin("1.inp");
    ofstream fout("1.txt");

    if (!fin) {
        cerr << "입력 파일을 열 수 없습니다." << endl;
        return 1;
    }

    if (!fout) {
        cerr << "출력 파일을 열 수 없습니다." << endl;
        return 1;
    }

    int T;
    fin >> T;

    for (int t = 0; t < T; ++t) {
        int n;
        string s;
        fin >> n >> s;

        if (s[0] == '(' || s[0] == ')') {
            // 주어진 괄호식을 이진 트리로 변환
            TreeNode* root = parenthesisToTree(s);
            vector<int> inorder, preorder;
            inorderTraversal(root, inorder);
            preorderTraversal(root, preorder);

            fout << n << " ";
            for (int val : preorder) {
                fout << val << " ";
            }
            fout << endl;
        } else {
            // 주어진 이진 트리를 괄호식으로 변환
            vector<int> inorder(n);
            for (int i = 0; i < n; ++i) {
                fin >> inorder[i];
            }
            TreeNode* root = buildTree(inorder);
            string parenthesis = treeToParenthesis(root);

            fout << parenthesis << endl;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
