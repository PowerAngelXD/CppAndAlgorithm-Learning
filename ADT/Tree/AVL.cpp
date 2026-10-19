#include <iostream>
#include <vector>

template<typename T>
struct Node {
    T element;
    int height = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    void inorder() {
        if (left) left->inorder();
        std::cout << element << " ";
        if (right) right->inorder();
    }
};

template<typename T>
class AVLTree {
    Node<T>* root;

    int getHeight(Node<T>* node) {
        return node ? node->height : -1;
    }

    void updateHeight(Node<T>* node = nullptr) {
        if (!node) node = root;

        if (!root) return;

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    inline int getBF(Node<T>* node) {
        return getHeight(node->left) - getHeight(node->right);
    }

    Node<T>* RRotate(Node<T>* target) {
        Node<T>* x = target->left;
        Node<T>* y = x->right;

        x->right = target;
        target->left = y;

        updateHeight(target);
        updateHeight(x);

        return x;
    }

    Node<T>* LRotate(Node<T>* target) {
        Node<T>* x = target->right;
        Node<T>* y = x->left;

        x->left = target;
        target->right = y;

        updateHeight(target);
        updateHeight(x);

        return x;
    }

    Node<T>* balance(Node<T>* node = nullptr) {
        if (!node) node = root;
        if (!root) return nullptr;

        updateHeight(node);
        int bf = getBF(node);

        if (bf > 1) {
            if (getBF(node->left) <= 0) {
                node->left = LRotate(node->left);
            }
            return RRotate(node);
        }
        if (bf < -1) {
            if (getBF(node->right) >= 0) {
                node->right = RRotate(node->right);
            }
            return LRotate(node);
        }

        return node;
    }

    Node<T>* insert(T val, Node<T>* cur) {
        if (val >= cur->element) {
            if (cur->right) {
                insert(val, cur->right);
            }
            else {
                cur->right = new Node<T>;
                cur->right->element = val;
            }
        }
        else if (val < cur->element) {
            if (cur->left) {
                insert(val, cur->left);
            }
            else {
                cur->left = new Node<T>;
                cur->left->element = val;
            }
        }

        updateHeight(cur);
        return balance(cur);
    }

    bool contains(T val, Node<T>* cur) {
        if (cur->element == val) return true;

        if (val >= cur->element) {
            if (cur->right) return contains(val, cur->right);
            return false;
        }

        if (cur->left) return contains(val, cur->left);
        return false;
    }

    T findMax(Node<T>* cur) {
        if (cur->right) {
            return findMax(cur->right);
        }

        return cur->element;
    }

    T findMin(Node<T>* cur) {
        if (cur->left) {
            return findMin(cur->left);
        }

        return cur->element;
    }
public:
    AVLTree(std::vector<T> list) {
        root = new Node<T>;
        root->element = list[0];
        for (std::size_t i = 1; i < list.size(); i ++) {
            insert(list[i]);
        }
    }

    void insert(T val) { root = insert(val, root); }
    bool contains(T val) { return contains(val, root); }
    T findMax() { return findMax(root); }
    T findMin() { return findMin(root); }

    void remove(T target) {
        if (!root) return;

        Node<T>* cur = root;
        Node<T>* parent = nullptr;
        while (cur != nullptr) {
            if (cur->element == target) break;

            parent = cur;
            if (target < cur->element)
                cur = cur->left;
            else
                cur = cur->right;
        }

        if (!cur) return;

        if (!cur->left || !cur->right) {
            Node<T>* child = cur->left ? cur->left : cur->right;
            if (cur != root) {
                if (parent->left == cur) {
                    parent->left = child;
                }
                else parent->right = child;
            }
            else {
                root = child;
            }

            delete cur;
        }
        else {
            Node<T>* node = cur->right;
            while (node->left) {
                node = node->left;
            }

            T tmp = node->element;
            remove(tmp);
            cur->element = tmp;
        }

        balance();
    }

    void inorderTraversal() {
        root->inorder();
        std::cout << std::endl;
    }
};

int main() {
    AVLTree<int> avl({30, 20, 40, 10, 25, 35, 50, 5, 15, 27, 45, 60});
    avl.inorderTraversal();
    avl.remove(20);

    avl.inorderTraversal();
}