#include <iostream>
#include <vector>

template<typename T>
struct Node {
    T value;
    Node* left = nullptr;
    Node* right = nullptr;

    void inorder() {
        if (left) left->inorder();
        std::cout << value << " ";
        if (right) right->inorder();
    }
};

template<typename T>
class BSTree {
    Node<T>* root = nullptr;

    void insert(T val, Node<T>* cur) {
        if (val >= cur->value) {
            if (cur->right) {
                insert(val, cur->right);
            }
            else {
                cur->right = new Node<T>;
                cur->right->value = val;
            }
        }
        else if (val < cur->value) {
            if (cur->left) {
                insert(val, cur->left);
            }
            else {
                cur->left = new Node<T>;
                cur->left->value = val;
            }
        }
    }

    bool contains(T val, Node<T>* cur) {
        if (cur->value == val) return true;

        if (val >= cur->value) {
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

        return cur->value;
    }

    T findMin(Node<T>* cur) {
        if (cur->left) {
            return findMin(cur->left);
        }

        return cur->value;
    }
public:
    explicit BSTree(std::vector<T> list) {
        root = new Node<T>;
        root->value = list[0];
        for (std::size_t i = 1; i < list.size(); i ++) {
            insert(list[i], root);
        }
    }

    void insert(T val) {
        insert(val, root);
    }

    bool contains(T val) {
        return contains(val, root);
    }

    T findMax() {
        return findMax(root);
    }

    T findMin() {
        return findMin(root);
    }

    void remove(T target) {
        if (!root) return;

        Node<T>* cur = root;
        Node<T>* parent = nullptr;
        while (cur != nullptr) {
            if (cur->value == target) break;

            parent = cur;
            if (target < cur->value)
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

            T tmp = node->value;
            remove(tmp);
            cur->value = tmp;
        }
    }

    void inorderTraversal() {
        root->inorder();
        std::cout << std::endl;
    }
};

int main() {
    BSTree<int> tree({3, 4, 2, 10, 8, 18, 15, 32, 77, 66});
    tree.inorderTraversal();
    std::cout << "TEST 2:" << std::endl;
    tree.insert(43);
    tree.inorderTraversal();
    std::cout << "check: " << tree.contains(2) << std::endl;
    std::cout << "check: " << tree.contains(99) << std::endl;
    std::cout << "check max: " << tree.findMax() << std::endl;
    std::cout << "TEST 3:" << std::endl;
    tree.remove(18);
    tree.inorderTraversal();
}