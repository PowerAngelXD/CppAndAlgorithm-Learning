#include <iostream>
#include <stdexcept>
#include <initializer_list>

template<typename T, class Allocator = std::allocator<T>>
struct Vector {
private:
    using allocTraits = std::allocator_traits<Allocator>;
    using size_type = std::size_t;

    T* _element = nullptr;
    size_type _size = 0;
    size_type _capacity = 0;
    Allocator _alloc;

    T* allocate(size_type n) {
        return allocTraits::allocate(_alloc, n);
    }

    void deallocate(T* ptr, size_type capacity) {
        allocTraits::deallocate(_alloc, ptr, capacity);
    }

    template<class... Args>
    void construct(T* p, Args&&... args) {
        allocTraits::construct(p, std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        allocTraits::destroy(_alloc, p);
    }

    void reallocate(size_type capacity) {
        size_type old_cap = _capacity;
        T* newElement = allocTraits::allocate(_alloc, capacity);

        size_type count = 0;
        try {
            for (size_type i = 0; i < _size; i ++) {
                allocTraits::construct(_alloc, newElement + i, std::move_if_noexcept(*(_element + i)));
                count ++;
            }
        }
        catch (...) {
            for (size_type i = 0; i < count; i ++) {
                allocTraits::destroy(_alloc, newElement + i);
            }
            allocTraits::deallocate(_alloc, newElement, capacity);
            throw;
        }

        for (size_type i = 0; i < _size; i ++) {
            allocTraits::destroy(_alloc, _element + i);
        }
        allocTraits::deallocate(_alloc, _element, old_cap);
        _capacity = capacity;
        _element = newElement;
    }

    void swap(Vector& vec) noexcept {
        std::swap(_element, vec._element);
        std::swap(_size, vec._size);
        std::swap(_capacity, vec._capacity);
        std::swap(_alloc, vec._alloc);
    }
public:
    using iterator = T*;
    using const_iterator = const T*;

    Vector()=default;
    Vector(std::initializer_list<T> list) {
        _size = list.size();
        _capacity = _size;
        _element = allocTraits::allocate(_alloc, _capacity);
        for (size_type i = 0; i < _size; i ++) {
            allocTraits::construct(_alloc, _element + i, list[i]);
        }
    }

    Vector(Vector&& vec) noexcept
    : _element(vec._element),
      _size(vec._size),
      _capacity(vec._capacity),
      _alloc(std::move(vec._alloc))
    {
        vec._size = 0;
        vec._capacity = 0;
        vec._element = nullptr;
    }

    Vector(const Vector& vec) {
        _size = vec._size;
        _capacity = vec._capacity;

        size_type count = 0;
        _element = allocTraits::allocate(_alloc, _capacity);
        try {
            for (size_type i = 0; i < _size; i ++) {
                allocTraits::construct(_alloc, _element + i, *(vec._element + i));
                count ++;
            }
        }
        catch (...) {
            for (size_type i = 0; i < count; i ++) {
                allocTraits::destroy(_alloc, _element + i);
            }
            allocTraits::deallocate(_alloc, _element, _capacity);
            throw;
        }
    }

    ~Vector() {
        if (_element == nullptr) return;

        for (size_type i = 0; i < _size; i ++) {
            allocTraits::destroy(_alloc, _element + i);
        }
        allocTraits::deallocate(_alloc, _element, _capacity);
    }

    template<class... Args>
    T& emplace_back(Args&&... args) {
        if (_size == _capacity) {
            reallocate(_capacity == 0 ? 1 : _capacity * 2);
        }

        T* p = _element + _size;
        allocTraits::construct(_alloc, p, std::forward<Args>(args)...);
        _size ++;

        return *p;
    }

    void push_back(T&& value) {
        emplace_back(std::move(value));
    }

    void push_back(const T& value) {
        emplace_back(value);
    }

    void push_back(std::initializer_list<T> values) {
        if (_capacity > _size + values.size()) {
            for (size_type i = 0; i < _size + values.size(); i ++) {
                allocTraits::construct(_alloc, _element + _size + i, values[i]);
            }
            _size = _size + values.size();
        }
        else {
            reallocate(_capacity == 0 ? values.size() : (_capacity + values.size()) * 1.5);
            for (size_type i = 0; i < _size + values.size(); i ++) {
                allocTraits::construct(_alloc, _element + _size + i, values[i]);
            }
            _size = _size + values.size();
        }
    }

    void reserve(const size_type size) {
        if (size <= _capacity) return;

        reallocate(size);
    }

    void pop_back() {
        if (_size != 0) {
            allocTraits::destroy(_alloc, _element + _size - 1);
            _size --;
        }
    }

    void clear() {
        for (size_type i = 0; i < _size; i ++) {
            allocTraits::destroy(_alloc, _element + i);
        }
        _size = 0;
    }

    void insert(T e) {

    }

    T& at(size_type index) {
        if (index < _size) return *(_element + index);
        else throw std::out_of_range("");
    }

    T& front() { return *_element; }
    T& back() { return *(_element + _size - 1); }


    T& operator[](size_type index) {
        return *(_element + index);
    }

    Vector& operator= (const Vector& vec) {
        Vector tmp(vec);
        swap(tmp);
        return *this;
    }

    Vector& operator= (Vector&& vec) noexcept {
        for (size_type i = 0; i < _size; i ++) {
            allocTraits::destroy(_alloc, _element + i);
        }

        _size = vec._size;
        _capacity = vec._capacity;
        _element = vec._element;
        _alloc = std::move(vec._alloc);

        vec._size = 0;
        vec._capacity = 0;
        vec._element = nullptr;
        return *this;
    }
};

int main() {
    using IntAlloc = std::allocator<int>;
    using Traits = std::allocator_traits<IntAlloc>;

    IntAlloc alloc;
    int* p = Traits::allocate(alloc, 3);
    Traits::construct(alloc, p, 123);
    Traits::construct(alloc, p + 1, 12345);
    Traits::construct(alloc, p + 2, 1234567);
    std::cout << *(p + 1) << std::endl;
    Traits::destroy(alloc, p);
    std::cout << *p << std::endl;

    Traits::deallocate(alloc, p, 3);

    return 0;
}