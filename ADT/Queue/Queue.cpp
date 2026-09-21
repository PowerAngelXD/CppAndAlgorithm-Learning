
#include <iostream>

template<typename T>
class SeqQueue {
    T* data = nullptr;
    std::size_t front = 0;
    std::size_t rear = 0;

    const static int size = 10;
public:
    SeqQueue() {
        data = new T[size];
    }

    std::size_t getSize() {
        return (rear - front + size) % size;
    }

    void push(const T& value) {
        if ((rear + 1) % size == front) 
            throw std::runtime_error("queue full");

        data[rear] = value;
        rear = (rear + 1) % size;
    }

    void pop() {
        if (rear == front) 
            throw std::runtime_error("queue empty");

        front = (front + 1) % size;
    }

    T& head() {
        return data[front];
    }
};

template<typename T>
class LinkedQueue {
    struct Node {
        T element;
        Node* next = nullptr;
    };

    Node* front = nullptr;
    Node* rear = nullptr;
public:
    LinkedQueue()=default;

    void push(const T& value) {
        if (front) {
            Node* node = new Node {value, nullptr};
            rear->next = node;
            rear = node;
        }
        else {
            front = new Node {value, nullptr};
            rear = front;
        }
    }

    void pop() {
        if (!front)
            throw std::runtime_error("queue is empty!");

        Node* node = front;
        front = front->next;
        delete node;
    }

    T& head() {
        return front->element;
    }
};

int main() {
    SeqQueue<int> q;
    q.push(2); q.push(4); q.push(8);
    std::cout << q.head() << std::endl;
    q.pop();
    std::cout << q.head() << std::endl;
    q.pop();
    std::cout << q.head() << std::endl;

    LinkedQueue<int> q1;
    q1.push(2); q1.push(4); q1.push(8);
    std::cout << q1.head() << std::endl;
    q1.pop();
    std::cout << q1.head() << std::endl;
    q1.pop();
    std::cout << q1.head() << std::endl;
}