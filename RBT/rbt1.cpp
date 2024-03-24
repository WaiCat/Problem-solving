# include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;
enum Color
{
    RED,
    BLACK
};
struct node
{
    int key;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    Color color = BLACK;
};
typedef node* NodePtr;

class RBT {
private:
    NodePtr root;
    NodePtr leafNode;

public:

    // key���� Ʈ���� �ִ��� ����
    // ���� �� nullptr ��ȯ
    NodePtr IsKey(int item)
    {
        NodePtr t = root;
        NodePtr parent = NULL;

        while (t != NULL && t->key != item)
        {
            parent = t;
            t = (item < parent->key) ? parent->left : parent->right; // ��� ��
        }
        return t;
    }

    void Insert(int item)
    {
        // x : ������ �� ã������ ������ | y : ������ ���� �θ���
        NodePtr x = this->root, y = nullptr;

        // ������ ��� ����
        NodePtr z = new node(); 
        z->key = item;
        z->color = RED;
        z->parent = nullptr;
        z->left = leafNode;
        z->right = leafNode;

        /*BST�� �Ϲ� ���� ����*/
        // leaf������ ������
        while (x != leafNode)
        {
            y = x;
            if (x->key < item)
                x = x->right;
            else
                x = x->left;
        }

        // ������ ����� �θ� ����
        z->parent = y;

        // ù ������ ��� root node
        if (y == nullptr)
            root = z;
        else if (z->key > y->key)
            y->right = z;
        else
            y->left = z;

        //z�� root�����
        if (z->parent == nullptr)
        {
            z->color = BLACK; // ��Ʈ ���� �׻� �������̴�. 
            return;
        }
        // z�� �Ҿƹ��� ��尡 root����� �ٷ� red
        if (z->parent->parent == nullptr)
        {
            return;
        }
        InsertFixUp(z);
        return;
    }

    void InsertFixUp(NodePtr z)
    {
        /*root ��尡 �ƴϰ� �θ� ���� red���*/
        // red �� �ڽ��� �� �� black�̿��� ��
        while (z != root && z->parent->color == RED)
        {
            NodePtr grandparent = z->parent->parent;
            NodePtr uncle = (z->parent == grandparent->left) ? grandparent->right : grandparent->left;
            bool side = (z->parent == grandparent->left) ? true : false; //if p[z]�� p[p[z]]�� ���� �ڽ��̸� 1 / �������̸� 0

            /*case 1*/
            // ������ red�� ��
            if (uncle && uncle->color == RED)
            {
                // �θ�� ������ blck, ���θ� red��
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED; 
                z = grandparent; // ���θ� ���� ���Ե� xó�� ���
            }

            /*case 2
                side == true ) p[z]�� p[p[z]]�� ���� �ڽ� �� ����̴�.
                side == false ) p[z]�� p[p[z]]�� ������ �ڽ� �� ����̴�. */
            // ������ black�� ��
            else
            {
                /*case 2-1*/
                // �θ� �Ҿƹ����� ���� �ڽ��̸� z=
                if (z == (side ? z->parent->right : z->parent->left))
                {
                    z = z->parent;
                    side ? RotateLeft(z) : RotateRight(z);
                }
                /*case 2-2*/
                z->parent->color = BLACK;
                grandparent->color = RED;
                side ? RotateRight(grandparent) : RotateLeft(grandparent);
            }
        }
        root->color = BLACK;
    }

    bool Delete(int item)
    {
        NodePtr z = IsKey(item);
        if (!z)
            return false;
        else
        {
            NodePtr x, y;
            Color OriginalColor = z->color;

            /*�ڽ��� ���ų� 1���� ���
                    ������ ���(z)�� �����̸� doulbe red�̹Ƿ� fix*/
            if (z->left == leafNode)
            {
                x = z->right;
                Transplant(z, z->right);
            }
            else if (z->right == leafNode)
            {
                x = z->left;
                Transplant(z, z->left);
            }
            else
            {
                y = tree_minimum(z->right);
                OriginalColor = y->color;
                x = y->right; //y�� ���� �ڽ��� ����.

                if (y->parent == z)
                {                  //z�� ������ �ڽ��� ���� ���� key
                    x->parent = y; // x�� leafnode�� ��, fix�ϰ� �� �� ���
                }
                else
                {
                    Transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                Transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (OriginalColor == BLACK)
            {
                DelteFixUp(x);
            }
        }
        return true;
    }

    void DelteFixUp(NodePtr x)
    {
        NodePtr s; //������� s

        //root�̰ų� double black �� ������ ����
        while (x != root && x->color == BLACK)
        {
            /* x�� p[x]�� �����ڽ��� ��� */
            if (x == x->parent->left)
            {
                s = x->parent->right;
                // case 1
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    RotateLeft(x->parent);
                    s = x->parent->right;
                }

                // case 2
                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    // case 3
                    if (s->right->color == BLACK)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        RotateRight(s);
                        s = x->parent->right;
                    }

                    // case 4
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    RotateLeft(x->parent);
                    x = root;
                }
            }

            /*x�� p[x]�� ������ �ڽ��� ���*/
            else
            {
                s = x->parent->left;
                // case 1
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    RotateRight(x->parent);
                    s = x->parent->left;
                }

                // case 2
                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    // case 3
                    if (s->left->color == BLACK)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        RotateLeft(s);
                        s = x->parent->left;
                    }
                    // case 4
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    RotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
        root->color = BLACK;
    }

    /* u�� ��ġ�� v�� �̽� */
    void Transplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }


    /*x�� �߽����� �������� ȸ��*/
    void RotateLeft(NodePtr x)
    {
        NodePtr y;

        y = x->right;
        x->right = y->left;
        if (y->left != leafNode)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        x->parent = y;
        y->left = x;
    }
    /*x�� �߽����� ���������� ȸ��*/
    void RotateRight(NodePtr y)
    {
        NodePtr x;

        x = y->left;
        y->left = x->right;
        if (x->right != leafNode)
        {
            x->right->parent = y;
        }
        x->parent = y->parent;

        if (!y->parent)
        {
            root = x;
        }
        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
        y->parent = x;
        x->right = y;
    }


    RBT()
    {
        leafNode = new node;
        leafNode->color = BLACK;
        leafNode->left = nullptr;
        leafNode->right = nullptr;
        leafNode->parent = nullptr;
        root = leafNode;
    }
    //�ּڰ� ã��
    NodePtr tree_minimum(NodePtr x)
    {
        while (x->left != leafNode)
        {
            x = x->left;
        }
        return x;
    }
    //�ִ� ã��
    NodePtr tree_maximum(NodePtr x)
    {
        while (x->right != leafNode)
        {
            x = x->right;
        }
        return x;
    }

    Color findNodeColor(int item) {
        return IsKey(item)->color;
    }
};

int main() {
    ifstream fin;
    ofstream fout;

    fin.open("0.inp"); 
    fout.open("0.out");

    RBT tree;

    while (true) {
        string command;
        int value;
        fin >> command >> value;
        if (value == -1) break;
        if (command == "i") tree.Insert(value);
        if (command == "c") {
            Color c = tree.findNodeColor(value);
            if (c == RED) fout << "color(" << value << "): RED" << endl;
            if (c == BLACK) fout << "color(" << value << "): BLACK" << endl;
        }
        if (command == "d") tree.Delete(value);
    }
}