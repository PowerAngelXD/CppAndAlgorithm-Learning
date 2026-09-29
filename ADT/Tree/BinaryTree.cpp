#include <iostream>
#include <chrono>

template<typename T>
class BinaryTree {
public:
    struct Node {
    private:
        Node* prev = nullptr;
    public:
        T element;
        Node* left = nullptr;
        Node* right = nullptr;

        bool leftThread = false;
        bool rightThread = false;

        Node(T val) { element = val; }

        void preorderTraversal(bool isTidy = false) {
            if (isTidy) std::cout << "{";
            std::cout << element;
            if (isTidy) { 
                if (left || right) std::cout << "->[";
            }
            if (left && !leftThread) {
                if (isTidy) std::cout << "l:";
                left->preorderTraversal(isTidy);
            }
            if (right && !rightThread) {
                if (isTidy) std::cout << "r:";
                right->preorderTraversal(isTidy);
            }
            if (isTidy) { 
                if (left || right) std::cout << "]";
                std::cout << "}";
            }
        }
        void postorderTraversal(bool isTidy = false) {
            if (isTidy) {
                std::cout << "{";
                if (left || right) std::cout << "[";
            }
            if (left && !leftThread) {
                if (isTidy) std::cout << "l:";
                left->postorderTraversal(isTidy);
            }
            if (right && !rightThread) {
                if (isTidy) std::cout << "r:";
                right->postorderTraversal(isTidy);
            }
            if (isTidy) {
                if (left || right) std::cout << "]<-";
            }
            std::cout << element;
            if (isTidy) std::cout << "}";
        }
        void inorderTraversal(bool isTidy = false) {
            if (isTidy) {
                std::cout << "{";
                if (left || right) std::cout << "[";
            }
            if (left && !leftThread) {
                left->inorderTraversal(isTidy);
                if (isTidy) std::cout << ":l]<-";
            }
            std::cout << element;
            if (right && !rightThread) {
                if (isTidy) std::cout << "->[r:";
                right->inorderTraversal(isTidy);
            }
            if (isTidy) {
                if (left || right) std::cout << "]";
            }
            if (isTidy) std::cout << "}";
        }
        
        int depth() {
            int ld = left?left->depth():0;
            int rd = right?right->depth():0;

            if (ld > rd) return ld + 1;
            else return rd + 1;
        }

        Node* copy() {
            Node* newNode = new Node{element, nullptr, nullptr};
            if (left)
                newNode->left = left->copy();
            if (right)
                newNode->right = right->copy();
            return newNode;
        }
    
        void createThread(Node* node) {
            if (!node) return;

            createThread(node->left);

            if (node->left == nullptr) {
                node->left = prev;
                node->leftThread = true;
            }

            if (prev != nullptr && prev->right == nullptr) {
                prev->right = node;
                prev->rightThread = true;
            }
            prev = node;

            createThread(node->right);
        }
    };
    Node* curNode = nullptr;
    Node* root = nullptr;
    bool isThreaded = false;

    BinaryTree()=delete;

    BinaryTree(T value) {
        root = new Node(value);
        curNode = root;
    }

    BinaryTree(const BinaryTree& other) {
        root = other.root ? other.root->copy() : nullptr;
        curNode = root;
    } 

    BinaryTree& setCursor(Node* node) {
        curNode = node;
        return *this;
    }

    Node* createNode(T value) {
        return new Node(value);
    }

    BinaryTree& createLeft(Node* node) {
        if (curNode->left)
            throw std::runtime_error("left branch already has a sub node");

        curNode->left = node;
        return *this;
    }

    BinaryTree& createRight(Node* node) {
        if (curNode->right)
            throw std::runtime_error("right branch already has a sub node");

        curNode->right = node;
        return *this;
    }

    void buildThread() {
        root->createThread(root);
        isThreaded = true;
    }

    Node* first() {
        if (!root) return nullptr;
        Node* curNode = root;
        while (curNode->left && !curNode->leftThread) {
            curNode = curNode->left;
        }

        return curNode;
    }

    Node* successor(Node* node) {
        if (!node) return nullptr;

        if (node->rightThread) return node->right;

        node = node->right;

        while (node && node->left && !node->leftThread) {
            node = node->left;
        }

        return node;
    }

    Node* end() {
        if (!root) return nullptr;
        Node* curNode = root;
        while (curNode->right && !curNode->rightThread) {
            curNode = curNode->right;
        }

        return curNode;
    }
};

int main() {
    BinaryTree<int> tree(1);
    tree.createLeft(tree.createNode(2)); tree.createRight(tree.createNode(5));
    tree.setCursor(tree.root->left);
    tree.createLeft(tree.createNode(7)); tree.createRight(tree.createNode(10));
    tree.setCursor(tree.root->left->right);
    tree.createRight(tree.createNode(3));

    tree.root->preorderTraversal();
    std::cout << std::endl;
    tree.root->postorderTraversal();
    std::cout << std::endl;
    tree.root->inorderTraversal();
    std::cout << std::endl;

    std::cout << tree.root->depth() << std::endl;

    tree.buildThread();
    std::cout << "After build thread:" << std::endl;
    auto normalStart = std::chrono::steady_clock::now();
    tree.root->inorderTraversal();
    auto normalEnd = std::chrono::steady_clock::now();
    std::cout << "Normal Inorder Travsersal, cost: " << std::chrono::duration_cast<std::chrono::microseconds>(normalEnd - normalStart).count() << "us" << std::endl;

    auto thdStart = std::chrono::steady_clock::now();
    BinaryTree<int>::Node* cur = tree.first();

    while (cur) {
        std::cout << cur->element;
        cur = tree.successor(cur);
    }
    auto thdEnd = std::chrono::steady_clock::now();
    std::cout << "Threaded Inorder Travsersal, cost: " << std::chrono::duration_cast<std::chrono::microseconds>(thdEnd - thdStart).count() << "us" << std::endl;
}