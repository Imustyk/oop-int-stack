#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>

class abstract_data_t {
public:
    abstract_data_t();
    abstract_data_t(size_t size);
    abstract_data_t(const int arr[], size_t size);
    abstract_data_t(const abstract_data_t& other);
    ~abstract_data_t();

    void clear();
    int at(int index) const;
    void resize(size_t newSize);
    void assign(size_t num, int value);
    size_t length() const;
    bool empty() const;
    void swap(abstract_data_t& other);

private:
    int* data;
    size_t size;
    size_t capacity;

    void reallocate(size_t newCapacity);
};

// Constructors
abstract_data_t::abstract_data_t() : data(NULL), size(0), capacity(0) {}

abstract_data_t::abstract_data_t(size_t size) : data(new int[size]), size(size), capacity(size) {
    std::fill(data, data + size, 0); // Инициализация всего массива нулями
}

abstract_data_t::abstract_data_t(const int arr[], size_t size) : data(new int[size]), size(size), capacity(size) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = arr[i];
    }
}

abstract_data_t::abstract_data_t(const abstract_data_t& other) : data(new int[other.capacity]), size(other.size), capacity(other.capacity) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// Destructor
abstract_data_t::~abstract_data_t() {
    clear();
}

// Methods
void abstract_data_t::clear() {
    delete[] data;
    data = NULL;
    size = 0;
    capacity = 0;
}

int abstract_data_t::at(int index) const {
    if (index < 0 || index >= static_cast<int>(size)) {
        return data[size - 1];
    }
    return data[index];
}

void abstract_data_t::resize(size_t newSize) {
    if (newSize > capacity) {
        reallocate(newSize);
    }
    if (newSize < size) {
        size = newSize;
    }
    else if (newSize > size) {
        std::fill(data + size, data + newSize, 0);
        size = newSize;
    }
}

void abstract_data_t::assign(size_t num, int value) {
    if (num > capacity) {
        reallocate(num);
    }
    std::fill(data, data + num, value);
    size = num;
}

size_t abstract_data_t::length() const {
    return size;
}

bool abstract_data_t::empty() const {
    return size == 0;
}

void abstract_data_t::swap(abstract_data_t& other) {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}

void abstract_data_t::reallocate(size_t newCapacity) {
    int* newData = new int[newCapacity];
    size_t newSize = std::min(newCapacity, size);
    for (size_t i = 0; i < newSize; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
    size = newSize;
}

void print(const abstract_data_t& stack) {
    for (size_t i = 0; i < stack.length(); ++i) {
        std::cout << stack.at(static_cast<int>(i)) << " ";
    }
    std::cout << std::endl;
}

// Main function
int main() {
    int array[] = { 1, 4, 7, 9 };
    abstract_data_t a(array, 4);
    assert(4 == a.length());
    assert(1 == a.at(0));
    assert(9 == a.at(10));
    print(a);
    abstract_data_t b(a);
    b.clear();
    assert(b.empty());
    abstract_data_t c;
    assert(c.empty());
    c.assign(3, 7);
    assert(3 == c.length());
    abstract_data_t d(5);
    assert(5 == d.length());
    d.resize(10);
    b.swap(d);
    assert(10 == b.length());
    assert(d.empty());

    return 0;
}
