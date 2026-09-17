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
class SeqList {
    T* data = nullptr;
    std::size_t size = 0;
public:
    SeqList()=default;
    SeqList(std::initializer_list<T> list) {
        size = list.size();
        data = new T[list.size()];

        std::size_t i = 0;
        for (auto it = list.begin(); it != list.end(); it ++) {
            data[i] = *it;
            i ++;
        }
    }

    std::size_t getSize() const { return size; }

    T& at(std::size_t index) {
        if (index >= size)
            throw std::out_of_range("");

        return data[index];
    }

    std::size_t find(const T& value) {
        for (std::size_t i = 0; i < size; i ++) {
            if (data[i] == value) return i;
        }
        throw std::runtime_error("cannot find");
    }

    void insert(std::size_t index, const T& value) {
        if (index >= size)
            throw std::out_of_range("");

        T* tmpData = new T[size + 1];

        for (std::size_t j = 0; j < index; ++j) {
            tmpData[j] = data[j];
        }

        tmpData[index] = value;

        for (std::size_t j = index; j < size; ++j) {
            tmpData[j + 1] = data[j];
        }

        delete[] data;
        data = tmpData;
        size ++;
    }

    void erase(std::size_t index) {
        if (index >= size)
            throw std::out_of_range("");

        T* tmpData = new T[size - 1];

        for (std::size_t j = 0; j < index; ++j) {
            tmpData[j] = data[j];
        }

        for (std::size_t j = index + 1; j < size; ++j) {
            tmpData[j - 1] = data[j];
        }

        delete[] data;
        data = tmpData;
        size --;
    }
};

int main() {
    SeqList<int> slist = SeqList<int>({1,3,4,5,6,10,9,6});
    slist.insert(4, 99);
    slist.erase(2);
    for (auto i = 0; i < slist.getSize(); i ++) {
        std::cout << slist.at(i) << std::endl;
    }
    int a[3] = {1, 2, 3};
    std::cout << &a << std::endl;
    std::cout << &a[0] << std::endl;
    
    return 0;
}