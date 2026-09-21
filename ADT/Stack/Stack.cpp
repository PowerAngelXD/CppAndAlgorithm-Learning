#include <iostream>
#define MAX_SIZE 25565

template<typename T>
class SeqStack {
    T* data = nullptr;
    T* top = nullptr;
public:
    SeqStack() {
        data = new T[MAX_SIZE];
        top = data;
    }
    // 这里默认push之后的总占用空间不会大于 MAX_SIZE
    void push(const T& value) {
        *(top ++) = value;
    }

    T& getTop() {
        return *(top - 1);
    }

    T pop() {
        return *(-- top);
    }
};

template<typename T>
class LinkedStack {
    struct Node {
        T element;
        Node* next = nullptr;
    };

    Node* data = nullptr;
public:
    LinkedStack()=default;

    void push(const T& value) {
        Node* node = new Node {value, data};
        data = node;
    }

    T& getTop() {
        if (!data)
            throw std::runtime_error("stack is empty!");

        return data->element;
    }

    void pop() {
        if (!data)
            throw std::runtime_error("stack is empty!");

        Node* ret = data;
        data = data->next;
        delete ret;
    }
};

int main() {
    SeqStack<int> stk;
    stk.push(2); stk.push(3);
    std::cout << stk.getTop() << std::endl;
    stk.pop();
    std::cout << stk.getTop() << std::endl;

    LinkedStack<int> stk1;
    stk1.push(3); stk1.push(9);
    std::cout << stk1.getTop() << std::endl;
    stk1.pop();
    std::cout << stk1.getTop() << std::endl;
}
