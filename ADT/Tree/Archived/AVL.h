#ifndef BALL_AVL_H
#define BALL_AVL_H
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

class AVLNode {
public:
    int data;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    int height = 0;

    AVLNode(int dt) : data(dt), height(0), left(nullptr), right(nullptr) {}

    static int getHeight(AVLNode* node) {
        return node ? node->height : -1;
    }

    void updateHeight() {
        int lh = getHeight(left);
        int rh = getHeight(right);
        height = 1 + (lh > rh ? lh : rh);
    }

    static int getBF(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    static AVLNode* RRotate(AVLNode* y) {
        if (!y || !y->left) return y;
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->updateHeight();
        x->updateHeight();

        return x;
    }

    static AVLNode* LRotate(AVLNode* x) {
        if (!x || !x->right) return x;
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->updateHeight();
        y->updateHeight();

        return y;
    }

    static AVLNode* balance(AVLNode* node) {
        if (!node) return nullptr;

        node->updateHeight();
        int bf = getBF(node);

        if (bf > 1) {
            if (getBF(node->left) < 0) {
                node->left = LRotate(node->left);
            }
            return RRotate(node);
        }
        if (bf < -1) {
            if (getBF(node->right) > 0) {
                node->right = RRotate(node->right);
            }
            return LRotate(node);
        }
        return node;
    }

    static AVLNode* insert(AVLNode* node, int d) {
        if (!node) return new AVLNode(d);

        if (d < node->data) {
            node->left = insert(node->left, d);
        } 
        else if (d > node->data) {
            node->right = insert(node->right, d);
        } 
        else {
            return node;
        }

        return balance(node);
    }

    static AVLNode* findMin(AVLNode* node) {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }

    static AVLNode* del(AVLNode* node, int d) {
        if (!node) return nullptr;

        if (d < node->data) {
            node->left = del(node->left, d);
        } 
        else if (d > node->data) {
            node->right = del(node->right, d);
        } 
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    delete node;
                    return nullptr;
                } 
                else {
                    AVLNode* toReturn = temp;
                    delete node;
                    return balance(toReturn);
                }
            } 
            else {
                AVLNode* temp = findMin(node->right);
                node->data = temp->data;
                node->right = del(node->right, temp->data);
            }
        }

        return balance(node);
    }

    bool has(int d) {
        if (d == data) return true;
        if (d < data) return left ? left->has(d) : false;
        return right ? right->has(d) : false;
    }

    void print(int depth = 0, std::string prefix = "", std::string label = "") {
        if (depth > 0) {
            std::cout << prefix << "|-- " << label << ": ";
        }
        std::cout << data << " (h=" << height << ")" << std::endl;

        std::string nextPrefix = prefix + (depth > 0 ? "    " : "");

        if (left || right) {
            if (left) {
                left->print(depth + 1, nextPrefix, "L");
            } 
            else {
                std::cout << nextPrefix << "|-- L: [NULL]" << std::endl;
            }

            if (right) {
                right->print(depth + 1, nextPrefix, "R");
            } 
            else {
                std::cout << nextPrefix << "|-- R: [NULL]" << std::endl;
            }
        }
    }
};

#endif
