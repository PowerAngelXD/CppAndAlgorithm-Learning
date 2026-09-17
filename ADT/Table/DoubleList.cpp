#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <concepts>

template <typename T>
concept Printable = requires(std::ostream& os, const T& value) {
    os << value;
};

template <typename T>
concept Equalable = requires(const T& a, const T& b) {
    { a == b } -> std::convertible_to<bool>;
};

template <typename T>
concept ElementType = Printable<T> && Equalable<T>;

template<ElementType T>
struct DoubleList {
private:
    struct ListNode {
        T element;
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
    };

    ListNode* head = nullptr;
    int listSize = 0;
public:
    DoubleList()=default;
    DoubleList(std::initializer_list<T> list) {
        if (list.size() == 0) return;

        head = new ListNode;
        head->element = *list.begin();
        ListNode* curNode = head;
        ListNode* prevNode = nullptr;
        for (auto it = list.begin() + 1; it != list.end(); it ++) {
            curNode->next = new ListNode;
            curNode->next->prev = curNode;
            curNode->next->element = *it;
            curNode = curNode->next;
        }
        listSize = list.size();
    }

    ~DoubleList() {
        if (!head) return;
        else {
            ListNode* curNode = head;
            while (curNode) {
                head = curNode->next;
                delete curNode;
            }
        }
    }

    void printAll() {
        ListNode* curNode = head;
        while (curNode) {
            std::cout << curNode->element << " ";
            curNode = curNode->next;
        }
        std::cout << std::endl;
    }

    bool isNull() {
        return !head;
    }

    bool has(T e) {
        ListNode* curNode = head;
        while (curNode) {
            if (curNode->element == e) return true;
            curNode = curNode->next;
        }
        return false;
    }

    bool find(T e) {
        ListNode* curNode = head;
        while (curNode) {
            if (curNode->element == e) return true;
            curNode = curNode->next;
        }
        return false;
    }

    T& at(int index) {
        ListNode* curNode = head;
        std::size_t i = 0;
        while (curNode) {
            if (i == index) return curNode->element;
            curNode = curNode->next;
            i ++;
        }
        throw std::runtime_error("cannot find");
    }

    void insert(int index, const T& e) {
        ListNode* curNode = head;
        std::size_t i = 0;
        while (curNode) {
            if (i == index) {
                ListNode* newNode = new ListNode;
                newNode->element = e;
                ListNode* after = curNode->next;
                curNode->next = newNode;
                newNode->prev = curNode;
                newNode->next = after;
                if (after)
                    after->prev = newNode;
                listSize ++;

                return;
            }
            curNode = curNode->next;
            i ++;
        }
        throw std::runtime_error("cannot insert");
    }

    void erase(int index) {
        ListNode* curNode = head;

        for (int i = 0; i < index; ++i) {
            curNode = curNode->next;
        }

        if (curNode->prev)
            curNode->prev->next = curNode->next;
        else
            head = curNode->next;

        if (curNode->next)
            curNode->next->prev = curNode->prev;

        delete curNode;
        listSize --;
    }

    int size() const {
        return listSize;
    }
};

int main() {
    DoubleList list = DoubleList<int>({1,2,3,4,5});
    list.printAll();
    list.insert(2, 112);
    list.printAll();
    list.erase(0);
    list.printAll();
    std::cout << list.size() << std::endl;
    std::cout << list.at(3) << std::endl;

    DoubleList list1 = DoubleList<int>();
    list1.printAll();
    std::cout << list1.isNull() << std::endl;
}