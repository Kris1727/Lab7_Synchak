#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Array {
private:
    size_t n;
    T* data;

public:
    Array() : n(0), data(nullptr) {}

    explicit Array(size_t size) : n(size), data(nullptr) {
        if (n > 0) data = new T[n]();
    }

    Array(size_t size, const T& value) : n(size), data(nullptr) {
        if (n > 0) {
            data = new T[n];
            for (size_t i = 0; i < n; ++i) data[i] = value;
        }
    }

    Array(const Array& other) : n(other.n), data(nullptr) {
        if (n > 0) {
            data = new T[n];
            for (size_t i = 0; i < n; ++i) data[i] = other.data[i];
        }
    }

    Array(Array&& other) noexcept : n(other.n), data(other.data) {
        other.n = 0;
        other.data = nullptr;
    }

    ~Array() { delete[] data; }

    Array& operator=(const Array& other) {
        if (this != &other) {
            T* tmp = nullptr;
            if (other.n > 0) {
                tmp = new T[other.n];
                for (size_t i = 0; i < other.n; ++i) tmp[i] = other.data[i];
            }
            delete[] data;
            data = tmp;
            n = other.n;
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            n = other.n;
            data = other.data;
            other.n = 0;
            other.data = nullptr;
        }
        return *this;
    }

    size_t size() const { return n; }

    T& operator[](size_t i) {
        if (i >= n) throw std::out_of_range("Індекс поза межами масиву");
        return data[i];
    }
    const T& operator[](size_t i) const {
        if (i >= n) throw std::out_of_range("Індекс поза межами масиву");
        return data[i];
    }

    bool swapWithMax(size_t k) {
        if (n == 0 || k >= n) return false;

        size_t maxIdx = 0;
        for (size_t i = 1; i < n; ++i)
            if (data[i] > data[maxIdx])
                maxIdx = i;

        T tmp = data[k];
        data[k] = data[maxIdx];
        data[maxIdx] = tmp;
        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const Array& a) {
        for (size_t i = 0; i < a.n; ++i) {
            out << a.data[i];
            if (i + 1 < a.n) out << ' ';
        }
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Array& a) {
        for (size_t i = 0; i < a.n; ++i) in >> a.data[i];
        return in;
    }
};

class Fraction {
private:
    long long num;
    long long den;

    void normalize() {
        if (den == 0) den = 1;
        if (den < 0) { den = -den; num = -num; }
    }

public:
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) { normalize(); }

    bool operator>(const Fraction& r) const { return num * r.den > r.num * den; }

    Fraction(const Fraction& r) : num(r.num), den(r.den) {}

    Fraction& operator=(const Fraction& r) {
        num = r.num;
        den = r.den;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f) {
        return out << f.num << '/' << f.den;
    }

    friend std::istream& operator>>(std::istream& in, Fraction& f) {
        in >> f.num >> f.den;
        f.normalize();
        return in;
    }
};

template <typename T>
void test(const char* title) {
    std::cout << "\n=== " << title << " ===\n";

    size_t n, k;
    std::cout << "Кількість елементів n: ";
    std::cin >> n;

    Array<T> arr(n);
    std::cout << "Введіть " << n << " елементів: ";
    std::cin >> arr;

    std::cout << "Індекс k (від 0 до " << n - 1 << "): ";
    std::cin >> k;

    std::cout << "Початковий масив: " << arr << '\n';

    if (arr.swapWithMax(k))
        std::cout << "Після обміну:     " << arr << '\n';
    else
        std::cout << "Помилка: некоректний індекс k або порожній масив\n";

    Array<T> copy(arr);
    std::cout << "Копія масиву:     " << copy << '\n';
}

int main() {
    test<int>("Масив int");
    test<Fraction>("Масив Fraction (вводьте: чисельник знаменник)");
    return 0;
}