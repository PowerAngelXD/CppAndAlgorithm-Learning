#ifndef BALL_HEAP_H
#define BALL_HEAP_H

#include <iostream>
#include <vector>

struct TreeNode {
    int val = 0;
    int height;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode()=default;
    TreeNode(int v): val(v) {}

    void print() {
        if (left == nullptr && right == nullptr)
            std::cout <<"("<< val <<")";
        else
            std::cout << val << ":{" ;

        if (left)
            left->print();
        if (right)
            right->print();

        if (!(left == nullptr && right == nullptr)) {
            std::cout << "}";
        }
    }
};

class BSTree {
    TreeNode* root;

public:
    BSTree()=default;
    BSTree(std::vector<int> list) {
        root = new TreeNode(list[0]);
        for (std::size_t i = 1; i < list.size(); i ++) {
            insert(list[i]);
        }
    }

    void insert(int element, TreeNode* current = nullptr) {
        if (!current) {
            // Is root
            if (element >= root->val) {
                if (root->right != nullptr) {
                    insert(element, root->right);
                }
                else {
                    root->right = new TreeNode(element);
                }
            }
            else {
                if (root->left != nullptr) {
                    insert(element, root->left);
                }
                else {
                    root->left = new TreeNode(element);
                }
            }
        }
        else {
            if (element >= current->val) {
                if (current->right != nullptr) {
                    insert(element, current->right);
                }
                else {
                    current->right = new TreeNode(element);
                }
            }
            else {
                if (current->left != nullptr) {
                    insert(element, current->left);
                }
                else {
                    current->left = new TreeNode(element);
                }
            }
        }
    }

    void del(int target) {
        if (root == nullptr)
            return;
        TreeNode *cur = root, *pre = nullptr;
        while (cur != nullptr) {
            if (cur->val == target)
                break;
            pre = cur;
            if (cur->val < target)
                cur = cur->right;
            else
                cur = cur->left;
        }
        if (cur == nullptr)
            return;
        if (cur->left == nullptr || cur->right == nullptr) {
            TreeNode *child = cur->left != nullptr ? cur->left : cur->right;
            if (cur != root) {
                if (pre->left == cur)
                    pre->left = child;
                else
                    pre->right = child;
            } else {
                root = child;
            }
            delete cur;
        }
        else {
            TreeNode *tmp = cur->right;
            while (tmp->left != nullptr) {
                tmp = tmp->left;
            }
            int tmpVal = tmp->val;
            del(tmp->val);
            cur->val = tmpVal;
        }
    }

    void print() {
        root->print();
    }

    bool has(int target) {
        TreeNode *cur = root;
        while (cur != nullptr) {
            if (cur->val < target)
                cur = cur->right;
            else if (cur->val > target)
                cur = cur->left;
            else
                break;
        }
        return cur;
    }
};



#endif