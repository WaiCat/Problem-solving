#include <fstream>
#include <iostream>

using namespace std;

struct Node {
  int key;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
  bool is_Red = false;
};

typedef Node *NodePtr;

class RedBlackNodeTree {
 private:
  NodePtr root;
  NodePtr leafNode;

  NodePtr searchNode(int value) {
    NodePtr temp = root;
    NodePtr parent = NULL;

    while (temp != NULL && temp->key != value) {
      parent = temp;
      temp = (value < parent->key) ? parent->left : parent->right;
    }
    return temp;
  }

  void insertNode(int value) {
    NodePtr node = this->root;
    NodePtr nodep = nullptr;
    NodePtr current = new Node();
    current->key = value;
    current->is_Red = true;
    current->parent = nullptr;
    current->left = leafNode;
    current->right = leafNode;

    while (node != leafNode) {
      nodep = node;
      if (node->key < value)
        node = node->right;
      else
        node = node->left;
    }

    current->parent = nodep;

    if (nodep == nullptr)
      root = current;
    else if (current->key > nodep->key)
      nodep->right = current;
    else
      nodep->left = current;

    if (current->parent == nullptr) {
      current->is_Red = false;
      return;
    }
    if (current->parent->parent == nullptr) {
      return;
    }
    insertFixUp(current);

    return;
  }

  void insertFixUp(NodePtr current) {
    while (current != root && current->parent->is_Red) {
      NodePtr grandparent = current->parent->parent;
      NodePtr uncle = (current->parent == grandparent->left)
                          ? grandparent->right
                          : grandparent->left;
      bool side = (current->parent == grandparent->left) ? true : false;

      if (uncle && uncle->is_Red) {
        current->parent->is_Red = false;
        uncle->is_Red = false;
        grandparent->is_Red = true;
        current = grandparent;
      }

      else {
        if (current ==
            (side ? current->parent->right : current->parent->left)) {
          current = current->parent;
          side ? rotateLeft(current) : rotateRight(current);
        }
        current->parent->is_Red = false;
        grandparent->is_Red = true;
        side ? rotateRight(grandparent) : rotateLeft(grandparent);
      }
    }
    root->is_Red = false;
  }

  bool deleteNode(int value) {
    NodePtr current = searchNode(value);
    if (!current)
      return false;
    else {
      NodePtr node, nodep;
      bool OriginalColor = current->is_Red;

      if (current->left == leafNode) {
        node = current->right;
        transplant(current, current->right);
      } else if (current->right == leafNode) {
        node = current->left;
        transplant(current, current->left);
      } else {
        nodep = minimum(current->right);
        OriginalColor = nodep->is_Red;
        node = nodep->right;

        if (nodep->parent == current) {
          node->parent = nodep;
        } else {
          transplant(nodep, nodep->right);
          nodep->right = current->right;
          nodep->right->parent = nodep;
        }
        transplant(current, nodep);
        nodep->left = current->left;
        nodep->left->parent = nodep;
        nodep->is_Red = current->is_Red;
      }
      delete current;
      if (!OriginalColor) {
        deleteFixUp(node);
      }
    }
    return true;
  }

  void deleteFixUp(NodePtr node) {
    NodePtr sibling;

    while (node != root && !node->is_Red) {
      if (node == node->parent->left) {
        sibling = node->parent->right;
        if (sibling->is_Red) {
          sibling->is_Red = false;
          node->parent->is_Red = true;
          rotateLeft(node->parent);
          sibling = node->parent->right;
        }
        if (!sibling->left->is_Red && !sibling->right->is_Red) {
          sibling->is_Red = true;
          node = node->parent;
        } else {
          if (!sibling->right->is_Red) {
            sibling->left->is_Red = false;
            sibling->is_Red = true;
            rotateRight(sibling);
            sibling = node->parent->right;
          }
          sibling->is_Red = node->parent->is_Red;
          node->parent->is_Red = false;
          sibling->right->is_Red = false;
          rotateLeft(node->parent);
          node = root;
        }
      }

      else {
        sibling = node->parent->left;
        if (sibling->is_Red) {
          sibling->is_Red = false;
          node->parent->is_Red = true;
          rotateRight(node->parent);
          sibling = node->parent->left;
        }

        if (!sibling->left->is_Red && !sibling->right->is_Red) {
          sibling->is_Red = true;
          node = node->parent;
        } else {
          if (!sibling->left->is_Red) {
            sibling->right->is_Red = false;
            sibling->is_Red = true;
            rotateLeft(sibling);
            sibling = node->parent->left;
          }
          sibling->is_Red = node->parent->is_Red;
          node->parent->is_Red = false;
          sibling->left->is_Red = false;
          rotateRight(node->parent);
          node = root;
        }
      }
    }
    node->is_Red = false;
  }

  void transplant(NodePtr node, NodePtr uncle) {
    if (node->parent == nullptr)
      root = uncle;
    else if (node == node->parent->left)
      node->parent->left = uncle;
    else
      node->parent->right = uncle;

    uncle->parent = node->parent;
  }

  void rotateLeft(NodePtr node) {
    NodePtr nodep;

    nodep = node->right;
    node->right = nodep->left;
    if (nodep->left != leafNode) {
      nodep->left->parent = node;
    }
    nodep->parent = node->parent;

    if (!node->parent) {
      root = nodep;
    } else if (node == node->parent->left) {
      node->parent->left = nodep;
    } else {
      node->parent->right = nodep;
    }
    node->parent = nodep;
    nodep->left = node;
  }

  void rotateRight(NodePtr nodep) {
    NodePtr node;

    node = nodep->left;
    nodep->left = node->right;
    if (node->right != leafNode) {
      node->right->parent = nodep;
    }
    node->parent = nodep->parent;

    if (!nodep->parent) {
      root = node;
    } else if (nodep == nodep->parent->left) {
      nodep->parent->left = node;
    } else {
      nodep->parent->right = node;
    }
    nodep->parent = node;
    node->right = nodep;
  }

 public:
  RedBlackNodeTree() {
    leafNode = new Node;
    leafNode->is_Red = false;
    leafNode->left = nullptr;
    leafNode->right = nullptr;
    leafNode->parent = nullptr;
    root = leafNode;
  }
  NodePtr minimum(NodePtr node) {
    while (node->left != leafNode) {
      node = node->left;
    }
    return node;
  }

  void insertValue(int value) { insertNode(value); }

  void deleteValue(int value) { deleteNode(value); }

  bool searchValue(int value) {
    NodePtr node = searchNode(value);
    return node->is_Red;
  }
};

int main() {
  RedBlackNodeTree bst;

  ifstream fin;
  ofstream fout;
  fin.open("rbt.inp");
  fout.open("rbt.out");

  char key;
  int value;

  while (fin >> key >> value) {
    if (value < 0) {
      break;
    }
    if (key == 'i') {
      bst.insertValue(value);
    } else if (key == 'c') {
      bool color = bst.searchValue(value);
      if (color) {
        fout << "color(" << value << "): RED" << endl;
      } else {
        fout << "color(" << value << "): BLACK" << endl;
      }
    } else if (key == 'd') {
      bst.deleteValue(value);
    }
  }

  return 0;
}
