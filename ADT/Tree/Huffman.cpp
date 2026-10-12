#include <iostream>
#include <vector>
#include <map>

template<typename T>
struct Node {
    T element;
    int weight = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    void preorderTraversal() {
        std::cout << weight << " ";
        if (left) {
            left->preorderTraversal();
        }
        if (right) {
            right->preorderTraversal();
        }
    }
};

template<typename T>
Node<T>* findMin(const std::vector<Node<T>*>& src) {
    auto min = *src.begin();

    for (auto node: src) {
        if (node->weight < min->weight)
            min = node;
    }

    return min;
}

template<typename T>
Node<T>* createHuffman(std::vector<T> data) {
    std::map<T, int> mapping;
    for (std::size_t i = 0; i < data.size(); i ++) {
        if (mapping.find(data[i]) == mapping.end())
            mapping[data[i]] = 1;
        else
            mapping[data[i]] ++;
    }

    std::vector<Node<T>*> seq;
    
    for (auto& [val, w]: mapping) {
        Node<T>* node = new Node<T>;
        node->element = val;
        node->weight = w;
        seq.push_back(node);
    }

    while (seq.size() > 1) {
        auto left = findMin(seq);
        for (auto it = seq.begin(); it != seq.end(); it ++) {
            if (*it == left) {
                seq.erase(it);
                break;
            }
        }

        auto right = findMin(seq);
        for (auto it = seq.begin(); it != seq.end(); it ++) {
            if (*it == right) {
                seq.erase(it);
                break;
            }
        }

        Node<T>* parent = new Node<T>;
        parent->left = left;
        parent->right = right;
        parent->weight = left->weight + right->weight;

        seq.push_back(parent);
    }

    return seq.front();
}

template<typename T>
void genHuffmanCode(Node<T>* node, std::string str = "") {
    if (!node) return;

    if (!node->left && !node->right) {
        std::cout << node->element << "=" << str;
        return;
    }

    genHuffmanCode(node->left, str + '0');
    genHuffmanCode(node->right, str + '1');
}

int main() {
    auto res = createHuffman<char>({'a', 'a', 'b', 'c', 'c', 'c', 'b', 'f', 'g', 'g', 'g', 'g', 'f', 'x', 'f'});
    res->preorderTraversal();
    std::cout << std::endl;
    genHuffmanCode(res);
    return 0;
}