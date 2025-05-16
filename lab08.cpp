#include <iostream>
#include <utility>

template<class T>
class MyUnique {
    T* p = nullptr;

public:
    MyUnique(T* ptr) : p(ptr) {}
    ~MyUnique() { delete p; }

    MyUnique(const MyUnique&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;

    MyUnique(MyUnique&& other) noexcept : p(other.p) { other.p = nullptr; }
    MyUnique& operator=(MyUnique&& other) noexcept {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
        return *this;
    }

    T* get() const { return p; }
    T& operator*() const { return *p; }
    T* operator->() const { return p; }
};

template<typename T, typename... Args>
MyUnique<T> Make_MyUnique(Args&&... args) {
    return MyUnique<T>(new T(std::forward<Args>(args)...));
}

template<class T>
class MyShared {
    T* p = nullptr;
    int* refCount = nullptr;

public:
    MyShared(T* ptr) : p(ptr), refCount(new int(1)) {}
    ~MyShared() { release(); }

    MyShared(const MyShared& other) : p(other.p), refCount(other.refCount) {
        if (refCount) (*refCount)++;
    }

    MyShared& operator=(const MyShared& other) {
        if (this != &other) {
            release();
            p = other.p;
            refCount = other.refCount;
            if (refCount) (*refCount)++;
        }
        return *this;
    }

    MyShared(MyShared&& other) noexcept : p(other.p), refCount(other.refCount) {
        other.p = nullptr;
        other.refCount = nullptr;
    }

    MyShared& operator=(MyShared&& other) noexcept {
        if (this != &other) {
            release();
            p = other.p;
            refCount = other.refCount;
            other.p = nullptr;
            other.refCount = nullptr;
        }
        return *this;
    }

    T* get() const { return p; }
    T& operator*() const { return *p; }
    T* operator->() const { return p; }

private:
    void release() {
        if (refCount && --(*refCount) == 0) {
            delete p;
            delete refCount;
        }
    }
};

template<typename T, typename... Args>
MyShared<T> Make_MyShared(Args&&... args) {
    return MyShared<T>(new T(std::forward<Args>(args)...));
}

class MyPoint {
    int x, y;
public:
    MyPoint(int x, int y) : x(x), y(y) {}
    void print() const { std::cout << "Point(" << x << ", " << y << ")" << std::endl; }
};

int main() {
    auto ptr1 = Make_MyUnique<MyPoint>(5, 10);
    ptr1->print();

    auto ptr2 = Make_MyShared<MyPoint>(3, 7);
    ptr2->print();

    return 0;
}