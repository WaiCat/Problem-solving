#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    int val;
    bool is_red;
    Node* left;
    Node* right;
    Node* parent;

    Node(int x, bool red = true) : val(x), is_red(red), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* root, int val) {
        if (root == nullptr) {
            return new Node(val);
        }

        if (val < root->val) {
            root->left = insert(root->left, val);
            root->left->parent = root;
        }
        else if (val > root->val) {
            root->right = insert(root->right, val);
            root->right->parent = root;
        }

        checkColor(root);

        return root;
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* remove(Node* root, int val) {
        if (root == nullptr) {
            return root;
        }

        if (val < root->val) {
            root->left = remove(root->left, val);
        }
        else if (val > root->val) {
            root->right = remove(root->right, val);
        }
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMinNode(root->right);
            root->val = temp->val;
            root->right = remove(root->right, temp->val);
        }
        
        checkColor(root);

        return root;
    }

    bool search(Node* root, int val) {
        if (root == nullptr) {
            return false;
        }

        if (val == root->val) {
            return root->is_red;
        }
        else if (val < root->val) {
            return search(root->left, val);
        }
        else {
            return search(root->right, val);
        }
    }

    void inorderTraversal(Node* root) {
        if (root == nullptr) {
            return;
        }

        inorderTraversal(root->left);
        cout << root->val << " ";
        inorderTraversal(root->right);
    }

    void checkColor(Node* root) {
        if(root->is_red){
            Node* parent = root->parent;
            Node* grandparent = (parent != nullptr) ? parent->parent : nullptr;
            if (grandparent != nullptr) {
                Node* uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;
                if(uncle != nullptr && uncle->is_red){
                    parent->is_red = false;
                    uncle->is_red = false;
                    grandparent->is_red = true;
                } else {
                    if (root == parent->right && parent == grandparent->left) {
                        // Left-Right Case: parent를 중심으로 좌회전 후 우회전
                        leftRotate(parent);
                        root = root->left;
                    } else if (root == parent->left && parent == grandparent->right) {
                        // Right-Left Case: parent를 중심으로 우회전 후 좌회전
                        rightRotate(parent);
                        root = root->right;
                    }
                    parent = root->parent;
                    grandparent = (parent != nullptr) ? parent->parent : nullptr;

                    // grandparent의 색상 변경 및 회전 수행
                    if (parent != nullptr && grandparent != nullptr) {
                        parent->is_red = false;
                        grandparent->is_red = true;
                        if (root == parent->left && parent == grandparent->left) {
                            rightRotate(grandparent);
                        } else {
                            leftRotate(grandparent);
                        }
                    }
                }
            }
        }
    }


    void leftRotate(Node* root) {
    if (root == nullptr || root->right == nullptr)
        return;

    Node* rightChild = root->right;
    root->right = rightChild->left;
    if (rightChild->left != nullptr)
        rightChild->left->parent = root;

    rightChild->parent = root->parent;
    if (root->parent != nullptr) {
        if (root == root->parent->left)
            root->parent->left = rightChild;
        else
            root->parent->right = rightChild;
    } else {
        root->parent = rightChild;
    }

    rightChild->left = root;
    root->parent = rightChild;
}

void rightRotate(Node* root) {
    if (root == nullptr || root->left == nullptr)
        return;

    Node* leftChild = root->left;
    root->left = leftChild->right;
    if (leftChild->right != nullptr)
        leftChild->right->parent = root;

    leftChild->parent = root->parent;
    if (root->parent != nullptr) {
        if (root == root->parent->left)
            root->parent->left = leftChild;
        else
            root->parent->right = leftChild;
    } else {
        root->parent = leftChild;
    }

    leftChild->right = root;
    root->parent = leftChild;
}

public:
    BST() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    void remove(int val) {
        root = remove(root, val);
    }

    bool search(int val) {
        return search(root, val);
    }

    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
  ifstream fin; 
  ofstream fout;
  fin.open("1.inp"); 
  fout.open("1.txt");

  BST bst;
  char key;
  int value;

  while(fin >> key >> value){
    if(value < 0){
      break;
    }

    if(key == 'i'){
        bst.insert(value);
    }else if(key == 'd'){
        bst.remove(value);
    }else if(key == 'c'){
        fout << "color(" << value << ") : ";
      if(bst.search(value)){
        fout << "RED" << endl;
      }else{
        fout << "BLACK" << endl;
      }
    }
  }

    fin.close();
    fout.close();

  return 0;
}

