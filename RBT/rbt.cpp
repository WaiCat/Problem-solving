#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    bool is_red;

    Node(int value, Node* p, bool red = true) : data(value), left(nullptr), right(nullptr), parent(p), is_red(red) {}
};

class BST {
private:
    Node* root;

    // 새로운 노드 생성
    Node* createNode(int value, Node* parent, bool red = true) {
        return new Node(value, parent, red);
    }

    // 왼쪽 회전
    void rotateLeft(Node* node) {
        Node* child = node->right;
        node->right = child->left;
        if (child->left != nullptr)
            child->left->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->left = node;
        node->parent = child;
    }

    // 오른쪽 회전
    void rotateRight(Node* node) {
        Node* child = node->left;
        node->left = child->right;
        if (child->right != nullptr)
            child->right->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->right)
            node->parent->right = child;
        else
            node->parent->left = child;
        child->right = node;
        node->parent = child;
    }

    void checkColor(Node*& current) {
    while (current != nullptr && current->parent != nullptr && current->parent->is_red) {
        Node* parent = current->parent;
        Node* grandparent = parent->parent;

        // Case 1: 부모 노드가 왼쪽 자식인 경우
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            // Case 1-1: 삼촌 노드가 빨간색인 경우
            if (uncle != nullptr && uncle->is_red) {
                parent->is_red = false;
                uncle->is_red = false;
                grandparent->is_red = true;
                current = grandparent;
            }
            // Case 1-2: 삼촌 노드가 검은색인 경우
            else {
                // Case 1-2-1: 현재 노드가 부모의 오른쪽 자식인 경우
                if (current == parent->right) {
                    current = parent;
                    rotateLeft(current);
                    parent = current->parent;
                }
                // Case 1-2-2: 현재 노드가 부모의 왼쪽 자식인 경우
                parent->is_red = false;
                grandparent->is_red = true;
                rotateRight(grandparent);
            }
        }
        // Case 2: 부모 노드가 오른쪽 자식인 경우 (위의 Case 1과 대칭적으로 처리)
        else {
            Node* uncle = grandparent->left;

            // Case 2-1: 삼촌 노드가 빨간색인 경우
            if (uncle != nullptr && uncle->is_red) {
                parent->is_red = false;
                uncle->is_red = false;
                grandparent->is_red = true;
                current = grandparent;
            }
            // Case 2-2: 삼촌 노드가 검은색인 경우
            else {
                // Case 2-2-1: 현재 노드가 부모의 왼쪽 자식인 경우
                if (current == parent->left) {
                    current = parent;
                    rotateRight(current);
                    parent = current->parent;
                }
                // Case 2-2-2: 현재 노드가 부모의 오른쪽 자식인 경우
                parent->is_red = false;
                grandparent->is_red = true;
                rotateLeft(grandparent);
            }
        }
    }
    root->is_red = false; // Root는 항상 검은색
}



    // 삽입 함수
    void insert(Node*& current, int value, Node* parent) {
        if (current == nullptr) {
            current = createNode(value, parent);
        } else if (value < current->data) {
            insert(current->left, value, current);
        } else if (value > current->data) {
            insert(current->right, value, current);
        }

        checkColor(current);
    }

    // 중위 순회를 사용하여 트리 출력
    void inorderTraversal(Node* current) {
        if (current != nullptr) {
            inorderTraversal(current->left);
            std::cout << "Value: " << current->data << " Is Red: " << (current->is_red ? "true" : "false") << std::endl;
            inorderTraversal(current->right);
        }
    }

    // 최소값 노드 찾기
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // 노드 삭제
    void remove(Node*& current, int key) {
        if (current == nullptr)
            return;

        if (key < current->data)
            remove(current->left, key);
        else if (key > current->data)
            remove(current->right, key);
        else {
            if (current->left == nullptr || current->right == nullptr) {
                Node* temp = current->left ? current->left : current->right;

                if (temp == nullptr) {
                    temp = current;
                    current = nullptr;
                } else {
                    *current = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(current->right);
                current->data = temp->data;
                remove(current->right, temp->data);
            }
        }
    }

public:
    BST() : root(nullptr) {}

    // 삽입 함수
    void insert(int value) {
        insert(root, value, nullptr);
    }

    void remove(int key) {
        remove(root, key);
    }

    // 탐색 함수
        Node* search(int value) {
        Node* current = root;
        while (current != nullptr && current->data != value) {
            if (value < current->data)
                current = current->left;
            else
                current = current->right;
        }
        return current;
    }

    // 트리 출력 함수
    void printTree() {
        inorderTraversal(root);
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
        } else if(key == 'd'){
            bst.remove(value);
        } else if(key == 'c'){
            fout << "color(" << value << "): ";
            if(bst.search(value)->is_red){
                fout << "RED" << endl;
            } else {
                fout << "BLACK" << endl;
            }
        }
    }

    fin.close();
    fout.close();

    return 0;
}
