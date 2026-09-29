#ifndef BALL_BINARYHEAP_H
#define BALL_BINARYHEAP_H
#include <iostream>
#include <vector>

// 以1为起始索引
class Heap {
    std::vector<int> arr;

    // 只是返回index，没有检查index是否合法
    inline int left(int n) {
        return n * 2;
    }

    // 只是返回index，没有检查index是否合法
    inline int right(int n) {
        return n * 2 + 1;
    }

    int find_son(int element) {
        int l = left(element);
        int r = right(element);
        int size = arr.size() - 1;

        if (l > size) {
            return -1;
        }

        if (r <= size && arr[r] > arr[l]) {
            return r;
        }

        return l;
    }
public:
    void up(int element) {
        for (int i = element; i > 1 && arr[i] > arr[i/2]; i /= 2) {
            std::swap(arr[i], arr[i/2]);
        }
    }

    void down(int element) {
        for (int i = element, t = find_son(element);
            t <= arr.size() && arr[t] > arr[i];
            i = t, t = find_son(i)) 
        {
            if (t == -1 || arr[i] >= arr[t]) break;
            std::swap(arr[i], arr[t]);
        }
    }

    void insert(int element) {
        arr.push_back(element);
        up(arr.size());
    }

    void pop() {
        std::swap(arr[1], arr[arr.size() - 1]);
        down(1);
    }

    int top() {
        return arr[1];
    }

    void build(std::vector<int> array) {
        arr.clear();
        arr.push_back(0);
        
        for (auto e: array) {
            arr.push_back(e);
        }

        for (int i = (arr.size() - 1) / 2; i > 0; i --) {
            down(i);
        }
    }

    void print(int index = 1, int depth = 0, std::string prefix = "Root") {
        if (index >= arr.size()) {
            return;
        }

        for (int i = 0; i < depth; ++i) {
            std::cout << "    ";
        }
        std::cout << "[" << prefix << "] " << arr[index] << std::endl;

        print(left(index), depth + 1, "L");
        
        print(right(index), depth + 1, "R");
    }
};

#endif // !BALL_BINARYHEAP_H