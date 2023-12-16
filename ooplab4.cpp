#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>

class abstract_data_t {
public:
    abstract_data_t() : data(nullptr), size(0), capacity(0) {}
    explicit abstract_data_t(size_t size) : data(new int[size]), size(size), capacity(size) {
        std::fill(data, data + size, 0);
    }
    abstract_data_t(const abstract_data_t& other) : data(new int[other.capacity]), size(other.size), capacity(other.capacity) {
        std::copy(other.data, other.data + size, data);
    }
    ~abstract_data_t() {
        delete[] data;
    }

    abstract_data_t& operator=(const abstract_data_t& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }

    bool operator==(const abstract_data_t& other) const {
        return size == other.size && std::equal(data, data + size, other.data);
    }

    bool operator!=(const abstract_data_t& other) const {
        return !(*this == other);
    }

    bool operator<(const abstract_data_t& other) const {
        return std::lexicographical_compare(data, data + size, other.data, other.data + other.size);
    }

    bool operator<=(const abstract_data_t& other) const {
        return !(other < *this);
    }

    bool operator>(const abstract_data_t& other) const {
        return other < *this;
    }

    bool operator>=(const abstract_data_t& other) const {
        return !(*this < other);
    }

    int& operator[](size_t index) {
        return data[index];
    }

    const int& operator[](size_t index) const {
        return data[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const abstract_data_t& adt) {
        for (size_t i = 0; i < adt.size; ++i) {
            os << adt.data[i] << " ";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, abstract_data_t& adt) {
        for (size_t i = 0; i < adt.size; ++i) {
            is >> adt.data[i];
        }
        return is;
    }

    bool contains(int value) const {
        return std::find(data, data + size, value) != data + size;
    }

    size_t count(int value) const {
        return std::count(data, data + size, value);
    }

    size_t length() const {
        return size;
    }

private:
    int* data;
    size_t size;
    size_t capacity;
};

int main(int argc, char const* argv[]) {
    std::stringstream ss{ "1 3 5 7 9" };
    abstract_data_t a(5);
    ss >> a;
    assert(5 == a.length());
    assert(1 == a[0]);
    assert(9 == a[4]);
    std::cout << a;
    abstract_data_t b{ a };
    assert(a == b);
    assert(3 == b[1]);
    assert(7 == b[3]);
    b[4] = 0;
    assert(0 == b[4]);
    assert(!b.contains(9));
    assert(b < a);
    assert(a > b);
    std::cout << b;
    abstract_data_t c;
    assert(0 == c.length());
    c = b;
    assert(b == c);
    c[1] = c[2] = 7;
    assert(7 == c[1]);
    assert(7 == c[2]);
    assert(3 == c.count(7));
    std::cout << c;
}
