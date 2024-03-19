#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


struct Node {
    int val;
    bool is_red;
    Node* left;
    Node* right;
    
    Node(int x, bool red = true) : val(x), is_red(red), left(nullptr), right(nullptr) {}
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
          } else if (val > root->val) {
              root->right = insert(root->right, val);
          }
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
          } else if (val > root->val) {
              root->right = remove(root->right, val);
          } else {
              if (root->left == nullptr) {
                  Node* temp = root->right;
                  delete root;
                  return temp;
              } else if (root->right == nullptr) {
                  Node* temp = root->left;
                  delete root;
                  return temp;
              }

              Node* temp = findMinNode(root->right);
              root->val = temp->val;
              root->right = remove(root->right, temp->val);
          }
          return root;
      }

      bool search(Node* root, int val) {
          if (root == nullptr) {
              return false;
          }

          if (val == root->val) {
              return true;
          } else if (val < root->val) {
              return search(root->left, val);
          } else {
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

  // while(fin >> key >> value){
  //   if(value < 0){
  //     break;
  //   }

  //   if(key == 'i'){

  //   }else if(key == 'd'){
      
  //   }else if(key == 'c'){
  //     bst.search(value);
  //   }
  // }


  bst.insert(5);
  bst.insert(3);
  bst.insert(7);
  bst.insert(1);
  bst.insert(4);
  bst.insert(6);
  bst.insert(8);

  cout << "Inorder Traversal: ";
  bst.inorderTraversal();

  cout << "Is 4 in the BST? " << (bst.search(4) ? "Yes" : "No") << endl;
  cout << "Is 10 in the BST? " << (bst.search(10) ? "Yes" : "No") << endl;

  bst.remove(2);
  cout << "Inorder Traversal after removing 2: ";
  bst.inorderTraversal();

  return 0;
}
