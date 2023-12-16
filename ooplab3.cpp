#include <cstdlib>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <iterator>

class iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;

    iterator(pointer ptr = nullptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    iterator& operator++() {
        ++m_ptr;
        return *this;
    }

    iterator operator++(int) {
        iterator temp = *this;
        ++(*this);
        return temp;
    }

    iterator& operator--() {
        --m_ptr;
        return *this;
    }

    iterator operator--(int) {
        iterator temp = *this;
        --(*this);
        return temp;
    }

    friend bool operator==(const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; }
    friend bool operator!=(const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; }

private:
    pointer m_ptr;
};

class reverse_iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;

    reverse_iterator(pointer ptr = nullptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    reverse_iterator& operator++() {
        --m_ptr;
        return *this;
    }

    reverse_iterator operator++(int) {
        reverse_iterator temp = *this;
        --(*this);
        return temp;
    }

    reverse_iterator& operator--() {
        ++m_ptr;
        return *this;
    }

    reverse_iterator operator--(int) {
        reverse_iterator temp = *this;
        ++(*this);
        return temp;
    }

    friend bool operator==(const reverse_iterator& a, const reverse_iterator& b) { return a.m_ptr == b.m_ptr; }
    friend bool operator!=(const reverse_iterator& a, const reverse_iterator& b) { return a.m_ptr != b.m_ptr; }

private:
    pointer m_ptr;
};

class abstract_data_t {
public:
    abstract_data_t() : data(nullptr), size(0), capacity(0) {}
    abstract_data_t(size_t size) : data(new int[size]), size(size), capacity(size) {
        std::fill(data, data + size, 0);
    }
    abstract_data_t(const int arr[], size_t size) : data(new int[size]), size(size), capacity(size) {
        std::copy(arr, arr + size, data);
    }
    abstract_data_t(const abstract_data_t& other) : data(new int[other.capacity]), size(other.size), capacity(other.capacity) {
        std::copy(other.data, other.data + size, data);
    }
    abstract_data_t(iterator first, iterator last) {
        ptrdiff_t dist = std::distance(first, last);
        if (dist < 0) {
            throw std::invalid_argument("Недопустимый диапазон итераторов");
        }
        size = static_cast<size_t>(dist);
        capacity = size;
        data = new int[size];


        int* temp = new int[size];
        std::copy(first, last, temp);
        std::copy(temp, temp + size, data);

        delete[] temp;
    }
    abstract_data_t(reverse_iterator first, reverse_iterator last) {
        ptrdiff_t dist = std::distance(first, last);
        if (dist < 0) {
            throw std::invalid_argument("Недопустимый диапазон обратных итераторов");
        }
        size = static_cast<size_t>(dist);
        capacity = size;
        data = new int[size];


        int* temp = new int[size];
        reverse_iterator temp_it = last;
        for (size_t i = 0; i < size; ++i) {
            --temp_it;
            temp[i] = *temp_it;
        }
        std::copy(temp, temp + size, data);

        delete[] temp;
    }

    ~abstract_data_t() {
        clear();
    }

    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    int at(int index) const {
        if (index < 0 || index >= static_cast<int>(size)) {
            throw std::out_of_range("Индекс выходит за пределы допустимого диапазона");
        }
        return data[index];
    }

    void resize(size_t newSize) {
        if (newSize > capacity) {
            reallocate(newSize);
        }
        if (newSize < size) {
            size = newSize;
        }
        else if (newSize > size) {
            std::fill(data + size, data + newSize, 0);
        }
        size = newSize;
    }

    void assign(size_t num, int value) {
        clear();
        size = num;
        capacity = num;
        data = new int[num];
        std::fill(data, data + num, value);
    }
    void assign(iterator first, iterator last) {
        clear();
        ptrdiff_t dist = std::distance(first, last);
        if (dist < 0) {
            throw std::invalid_argument("Недопустимый диапазон итераторов");
        }
        size = static_cast<size_t>(dist);
        capacity = size;
        data = new int[size];
        std::copy(first, last, data);
    }

    size_t length() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    void swap(abstract_data_t& other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }

    static bool is_equal(const abstract_data_t& a, const abstract_data_t& b) {
        return a.size == b.size && std::equal(a.data, a.data + a.size, b.data);
    }

    iterator begin() const {
        return iterator(data);
    }

    iterator end() const {
        return iterator(data + size);
    }
    reverse_iterator rbegin() const {
        return reverse_iterator(data + size - 1);
    }

    reverse_iterator rend() const {
        return reverse_iterator(data - 1);
    }

private:
    int* data;
    size_t size;
    size_t capacity;

    void reallocate(size_t newCapacity) {
        int* newData = new int[newCapacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
        capacity = newCapacity;
        if (newCapacity > size) {
            std::fill(data + size, data + newCapacity, 0);
        }
    }
};

int main(int argc, char const* argv[])
{
    int array[] = { 19, 47, 74, 91 };

    abstract_data_t a(array, 4);
    for (auto it = a.begin(); it != a.end(); ++it) std::cout << *it << " ";

    abstract_data_t b(a.begin(), a.end());
    assert(abstract_data_t::is_equal(a, b));
    for (auto&& it : b) std::cout << it << " ";

    abstract_data_t c(b.begin(), b.end());
    assert(std::equal(c.begin(), c.end(), b.begin()));
    for (auto it = c.rbegin(); it != c.rend(); ++it) std::cout << *it << " ";

    abstract_data_t d(c.rbegin(), c.rend());
    for (auto it = d.rbegin(); it != d.rend(); ++it) std::cout << *it << " ";

    return 0;
}
