#ifndef BALL_TREE_H
#define BALL_TREE_H

#include <iostream>
#include <vector>
#include <stack>
#include <map>

struct TreeNode {
    int val = 0;
    std::vector<TreeNode*> subs;

    TreeNode()=default;
    TreeNode(int v): val(v) {}

    TreeNode& addChild(int v) {
        subs.push_back(new TreeNode(v));
        return *this;
    }

    void preorderTraversal() {
        if (subs.empty())
            std::cout <<"("<< val <<")";
        else
            std::cout << val << ":{" ;

        for (auto node: subs) {
            node->preorderTraversal();
        }

        if (!subs.empty()) {
            std::cout << "}";
        }
    }

    void postorderTraversal() {
        std::cout << "{";

        for (auto node: subs) {
            node->postorderTraversal();
        }

        if (subs.empty())
            std::cout << "sub: " << val << "}";
        else
            std::cout << "(" << val << ")}";
    }
};

void test_normal_tree() {
    auto root = TreeNode();

    root.subs.push_back(new TreeNode(1));
    root.subs.push_back(new TreeNode(2));
    root.subs.push_back(new TreeNode(3));
    root.subs.push_back(new TreeNode(4));

    root.subs.at(0)->subs.push_back(new TreeNode(10));
    root.subs.at(0)->subs.push_back(new TreeNode(11));
    root.subs.at(0)->subs.push_back(new TreeNode(12));
    root.subs.at(1)->subs.push_back(new TreeNode(13));
    root.subs.at(1)->subs.push_back(new TreeNode(14));
    root.subs.at(3)->subs.push_back(new TreeNode(15));

    root.postorderTraversal();
}

template<typename T>
struct BinaryNode {
    T val;
    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;

    BinaryNode(T v): val(v) {}

    void preorderTraversal() {
        if (this == nullptr) return;
        
        std::cout << "[" << val;

        left->preorderTraversal();
        right->preorderTraversal();
        std::cout<< "]";
    }
};

void BSTinsert(BinaryNode<int>*& bin_tree, int element) {
    if (!bin_tree) {
        bin_tree = new BinaryNode(element);
        return;
    }

    if (bin_tree->val > element) {
        BSTinsert(bin_tree->left, element);
    }
    else {
        BSTinsert(bin_tree->right, element);
    }
}

void test_BST() {
    // 按照书p80的二叉搜寻树进行构造
    auto root = new BinaryNode(6);
    root->left = new BinaryNode(2);
    root->left->left = new BinaryNode(1);
    root->left->right = new BinaryNode(4);
    root->left->right->left = new BinaryNode(3);

    root->right = new BinaryNode(8);
    //
    BSTinsert(root, 19);
    BSTinsert(root, 5);
    root->preorderTraversal();
}

void binaryExprConstruct(std::string expr) {
    std::stack<BinaryNode<char>*> runtime;
    for (auto ch: expr) {
        if (isdigit(ch))
            runtime.push(new BinaryNode(ch));
        else {
            auto right = runtime.top(); runtime.pop();
            auto left = runtime.top(); runtime.pop();
            auto node = new BinaryNode(ch);
            node->left = left;
            node->right = right;
            runtime.push(node);
        }
    }

    runtime.top()->preorderTraversal();
}

BinaryNode<char>* preInBuild(std::string preorder, std::string inorder) {
    if (preorder.empty()) return nullptr;

    char rootVal = preorder[0];
    auto root = new BinaryNode<char>(rootVal);

    int split = inorder.find(rootVal);

    root->left = preInBuild(preorder.substr(1, split), inorder.substr(0, split));
    root->right = preInBuild(preorder.substr(1 + split), inorder.substr(split + 1));

    return root;
}

BinaryNode<char>* postInBuild(std::string postorder, std::string inorder) {
    if (postorder.empty()) return nullptr;

    char rootVal = postorder.back();
    auto root = new BinaryNode<char>(rootVal);

    int split = inorder.find(rootVal);

    root->left = postInBuild(postorder.substr(0, split), inorder.substr(0, split));
    root->right = postInBuild(postorder.substr(split, postorder.size() - 1 - split), inorder.substr(split + 1));
    return root;
}
#endif