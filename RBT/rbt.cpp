#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    bool is_red;

    Node(const T& value)
        : data(value), left(nullptr), right(nullptr), parent(nullptr), is_red(true) {}
};

template <typename T>
class RedBlackTree {
private:
    Node<T>* root;

    void rotateLeft(Node<T>*&);
    void rotateRight(Node<T>*&);
    void fixInsertion(Node<T>*&);
    void fixDeletion(Node<T>*);
    void transplant(Node<T>*, Node<T>*);

public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree() {}

    void insert(const T&);
    void remove(const T&);

    Node<T>* search(const T&);
    Node<T>* minimum(Node<T>*);
    Node<T>* maximum(Node<T>*);
    Node<T>* successor(Node<T>*);
    Node<T>* predecessor(Node<T>*);

    void inorderTraversal(Node<T>*);
    void preorderTraversal(Node<T>*);
    void postorderTraversal(Node<T>*);

    void printTree(Node<T>*, int);
};

template <typename T>
void RedBlackTree<T>::insert(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    Node<T>* parent = nullptr;
    Node<T>* current = root;

    while (current != nullptr) {
        parent = current;
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;

    if (parent == nullptr)
        root = newNode;
    else if (value < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsertion(newNode);
}

template <typename T>
void RedBlackTree<T>::remove(const T& value) {
    Node<T>* nodeToRemove = search(value);

    if (nodeToRemove == nullptr)
        return;

    Node<T>* x;
    Node<T>* y = nodeToRemove;
    bool yOriginalColor = y->is_red;

    if (nodeToRemove->left == nullptr) {
        x = nodeToRemove->right;
        transplant(nodeToRemove, nodeToRemove->right);
    } else if (nodeToRemove->right == nullptr) {
        x = nodeToRemove->left;
        transplant(nodeToRemove, nodeToRemove->left);
    } else {
        y = minimum(nodeToRemove->right);
        yOriginalColor = y->is_red;
        x = y->right;
        if (y->parent == nodeToRemove)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = nodeToRemove->right;
            y->right->parent = y;
        }
        transplant(nodeToRemove, y);
        y->left = nodeToRemove->left;
        y->left->parent = y;
        y->is_red = nodeToRemove->is_red;
    }

    if (!yOriginalColor)
        fixDeletion(x);

    delete nodeToRemove;
}

template <typename T>
Node<T>* RedBlackTree<T>::search(const T& value) {
    Node<T>* current = root;

    while (current != nullptr && current->data != value) {
        if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }

    return current;
}

int main() {
    RedBlackTree<int> tree;

    ifstream fin; 
    ofstream fout;
    fin.open("1.inp"); 
    fout.open("1.txt");

    char key;
    int value;

    while (fin >> key >> value) {
        switch (key) {
            case 'i':
                tree.insert(value);
                break;
            case 'c':
                {
                    fout << "color(" << value << "): ";
                    Node<int>* result = tree.search(value);

                    if(result->is_red){
                        fout << "RED" << endl;
                    }else{
                        fout << "BLACK" << endl;
                    }
                }
                break;
            case 'd':
                tree.remove(value);
                break;
            default:
                cerr << "Invalid key: " << key << endl;
        }
    }
    return 0;
}
