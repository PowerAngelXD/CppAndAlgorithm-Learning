#include <iostream>
#include <vector>
#include <assert.h>

enum Color {
    Red, Black
};

template<typename T>
struct Node {
    T value;
    Color color = Color::Black;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(T val, Color c, Node* p): value(val), color(c), parent(p) {}

    void inorder(std::vector<T>& result) const {
        if (left) left->inorder(result);
        result.push_back(value);
        if (right) right->inorder(result);
    }
};

template<typename T>
class RBTree {
public:
    using RBNode = Node<T>*;
private:
    RBNode root = nullptr;

    RBNode RRotate(Node<T>* node) {
        RBNode p = node->parent;
        RBNode x = node->left;
        RBNode y = x->right;
        x->right = node;
        node->parent = x;
        node->left = y;
        if (y) {
            y->parent = node;
        }

        if (!p) {
            root = x;
            root->parent = nullptr;
            return root;
        }

        if (p->left == node) {
            p->left = x;
            x->parent = p;
        }
        else if (p->right == node) {
            p->right = x;
            x->parent = p;
        }

        return x;
    }

    RBNode LRotate(Node<T>* node) {
        RBNode p = node->parent;
        RBNode x = node->right;
        RBNode y = x->left;
        x->left = node;
        node->parent = x;
        node->right = y;
        if (y) {
            y->parent = node;
        }

        if (!p) {
            root = x;
            root->parent = nullptr;
            return root;
        }

        if (p->left == node) {
            p->left = x;
            x->parent = p;
        }
        else if (p->right == node) {
            p->right = x;
            x->parent = p;
        }

        return x;
    }

    void clear(RBNode node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
public:
    explicit RBTree() {

    }
};

int main() {

}