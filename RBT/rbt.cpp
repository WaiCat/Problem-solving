#include <iostream>
#include <fstream>

using namespace std;

const bool RED = true;
const bool BLACK = false;

struct Node
{
  int data;
  Node *parent;
  Node *left;
  Node *right;
  bool is_red;
};

typedef Node *NodePtr;

class RedBlackTree
{
private:
  NodePtr root;
  NodePtr TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent)
  {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->is_red = false;
  }

  NodePtr searchTreeHelper(NodePtr node, int key)
  {
    if (node == TNULL || key == node->data)
    {
      return node;
    }

    if (key < node->data)
    {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  void deleteFix(NodePtr x)
  {
    NodePtr s;
    while (x != root && !x->is_red)
    {
      if (x == x->parent->left)
      {
        s = x->parent->right;
        if (s->is_red)
        {
          s->is_red = false;
          x->parent->is_red = true;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (!s->left->is_red && !s->right->is_red)
        {
          s->is_red = true;
          x = x->parent;
        }
        else
        {
          if (!s->right->is_red)
          {
            s->left->is_red = false;
            s->is_red = true;
            rightRotate(s);
            s = x->parent->right;
          }

          s->is_red = x->parent->is_red;
          x->parent->is_red = false;
          s->right->is_red = false;
          leftRotate(x->parent);
          x = root;
        }
      }
      else
      {
        s = x->parent->left;
        if (s->is_red)
        {
          s->is_red = false;
          x->parent->is_red = true;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (!s->right->is_red && !s->right->is_red)
        {
          s->is_red = true;
          x = x->parent;
        }
        else
        {
          if (!s->left->is_red)
          {
            s->right->is_red = false;
            s->is_red = true;
            leftRotate(s);
            s = x->parent->left;
          }

          s->is_red = x->parent->is_red;
          x->parent->is_red = false;
          s->left->is_red = false;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->is_red = false;
  }

  void rbTransplant(NodePtr u, NodePtr v)
  {
    if (u->parent == nullptr)
    {
      root = v;
    }
    else if (u == u->parent->left)
    {
      u->parent->left = v;
    }
    else
    {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(NodePtr node, int key)
  {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL)
    {
      if (node->data == key)
      {
        z = node;
      }

      if (node->data <= key)
      {
        node = node->right;
      }
      else
      {
        node = node->left;
      }
    }

    if (z == TNULL)
    {
      return;
    }

    y = z;
    bool y_original_color = y->is_red;
    if (z->left == TNULL)
    {
      x = z->right;
      rbTransplant(z, z->right);
    }
    else if (z->right == TNULL)
    {
      x = z->left;
      rbTransplant(z, z->left);
    }
    else
    {
      y = minimum(z->right);
      y_original_color = y->is_red;
      x = y->right;
      if (y->parent == z)
      {
        x->parent = y;
      }
      else
      {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->is_red = z->is_red;
    }
    delete z;
    if (!y_original_color)
    {
      deleteFix(x);
    }
  }

  void insertFix(NodePtr k)
  {
    NodePtr u;
    while (k->parent->is_red)
    {
      if (k->parent == k->parent->parent->right)
      {
        u = k->parent->parent->left;
        if (u->is_red)
        {
          u->is_red = false;
          k->parent->is_red = false;
          k->parent->parent->is_red = true;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->left)
          {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->is_red = false;
          k->parent->parent->is_red = true;
          leftRotate(k->parent->parent);
        }
      }
      else
      {
        u = k->parent->parent->right;

        if (u->is_red)
        {
          u->is_red = false;
          k->parent->is_red = false;
          k->parent->parent->is_red = true;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->right)
          {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->is_red = false;
          k->parent->parent->is_red = true;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root)
      {
        break;
      }
    }
    root->is_red = false;
  }

public:
  RedBlackTree()
  {
    TNULL = new Node;
    TNULL->is_red = false;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  NodePtr searchTree(int k)
  {
    return searchTreeHelper(this->root, k);
  }

  NodePtr minimum(NodePtr node)
  {
    while (node->left != TNULL)
    {
      node = node->left;
    }
    return node;
  }
  NodePtr maximum(NodePtr node)
  {
    while (node->right != TNULL)
    {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x)
  {
    if (x->right != TNULL)
    {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right)
    {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x)
  {
    if (x->left != TNULL)
    {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left)
    {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x)
  {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL)
    {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->left)
    {
      x->parent->left = y;
    }
    else
    {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodePtr x)
  {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL)
    {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->right)
    {
      x->parent->right = y;
    }
    else
    {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  void insert(int key)
  {
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->is_red = true;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL)
    {
      y = x;
      if (node->data < x->data)
      {
        x = x->left;
      }
      else
      {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr)
    {
      root = node;
    }
    else if (node->data < y->data)
    {
      y->left = node;
    }
    else
    {
      y->right = node;
    }

    if (node->parent == nullptr)
    {
      node->is_red = false;
      return;
    }

    if (node->parent->parent == nullptr)
    {
      return;
    }

    insertFix(node);
  }

  NodePtr getRoot()
  {
    return this->root;
  }

  bool searchValue(int value)
  {
    NodePtr node = searchTree(value);
    if (node == nullptr)
      return false;
    else
      return node->is_red;
  }

  void deleteNode(int data)
  {
    deleteNodeHelper(this->root, data);
  }
};

int main()
{
  RedBlackTree bst;

  ifstream fin("rbt.inp");
  ofstream fout("rbt.out");

  char key;
  int value;

  while (true)
  {
    fin >> key >> value;
    if (value < 0)
    {
      break;
    }
    if (key == 'i')
    {
      bst.insert(value);
    }
    else if (key == 'c')
    {
      bool color = bst.searchValue(value);
      if (color)
      {
        fout << "color(" << value << "): RED" << endl;
      }
      else
      {
        fout << "color(" << value << "): BLACK" << endl;
      }
    }
    else if (key == 'd')
    {
      bst.deleteNode(value);
    }
  }

  fin.close();
  fout.close();

  return 0;
}