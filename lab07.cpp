#include <iostream>
#include <utility>

using namespace std;

// Часть 1: Реализация unique_ptr
template<class T>
class MyUnique {
    T* p = nullptr;

public:
    // Конструктор с сырым указателем
    explicit MyUnique(T* ptr = nullptr) : p(ptr) {}
    
    // Запрет копирования
    MyUnique(const MyUnique&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;
    
    // Перемещение
    MyUnique(MyUnique&& other) noexcept : p(other.p) {
        other.p = nullptr;
    }
    
    MyUnique& operator=(MyUnique&& other) noexcept {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
        return *this;
    }
    
    // Деструктор
    ~MyUnique() {
        delete p;
    }
    
    // Получение сырого указателя
    T* get() const {
        return p;
    }
    
    // Перегрузка операторов
    T& operator*() const {
        return *p;
    }
    
    T* operator->() const {
        return p;
    }
};

// Функция создания MyUnique
template<typename T, typename... Args>
MyUnique<T> Make_MyUnique(Args&&... args) {
    return MyUnique<T>(new T(forward<Args>(args)...);
}

// Часть 2: Реализация shared_ptr
template<class T>
class MyShared {
    T* p = nullptr;
    size_t* count = nullptr;

    void release() {
        if (count && --(*count) == 0) {
            delete p;
            delete count;
        }
        p = nullptr;
        count = nullptr;
    }

public:
    // Конструктор с сырым указателем
    explicit MyShared(T* ptr = nullptr) : p(ptr), count(ptr ? new size_t(1) : nullptr) {}
    
    // Копирование
    MyShared(const MyShared& other) : p(other.p), count(other.count) {
        if (count) ++(*count);
    }
    
    MyShared& operator=(const MyShared& other) {
        if (this != &other) {
            release();
            p = other.p;
            count = other.count;
            if (count) ++(*count);
        }
        return *this;
    }
    
    // Перемещение
    MyShared(MyShared&& other) noexcept : p(other.p), count(other.count) {
        other.p = nullptr;
        other.count = nullptr;
    }
    
    MyShared& operator=(MyShared&& other) noexcept {
        if (this != &other) {
            release();
            p = other.p;
            count = other.count;
            other.p = nullptr;
            other.count = nullptr;
        }
        return *this;
    }
    
    // Деструктор
    ~MyShared() {
        release();
    }
    
    // Получение сырого указателя
    T* get() const {
        return p;
    }
    
    // Перегрузка операторов
    T& operator*() const {
        return *p;
    }
    
    T* operator->() const {
        return p;
    }
    
    // Количество ссылок
    size_t use_count() const {
        return count ? *count : 0;
    }
};

// Функция создания MyShared
template<typename T, typename... Args>
MyShared<T> Make_MyShared(Args&&... args) {
    return MyShared<T>(new T(forward<Args>(args)...);
}

// Тестовый класс для демонстрации
class MyPoint {
    int x, y;
public:
    MyPoint(int x, int y) : x(x), y(y) {
        cout << "MyPoint constructed: " << x << ", " << y << endl;
    }
    ~MyPoint() {
        cout << "MyPoint destroyed: " << x << ", " << y << endl;
    }
    void print() const {
        cout << "Point: (" << x << ", " << y << ")" << endl;
    }
};

int main() {
    // Демонстрация MyUnique
    {
        cout << "=== MyUnique Demo ===" << endl;
        auto p1 = Make_MyUnique<MyPoint>(1, 2);
        p1->print();
        
        // MyUnique<MyPoint> p2 = p1; // Ошибка: копирование запрещено
        MyUnique<MyPoint> p3 = move(p1); // Перемещение разрешено
        if (!p1.get()) cout << "p1 is now empty" << endl;
        p3->print();
    }
    
    // Демонстрация MyShared
    {
        cout << "\n=== MyShared Demo ===" << endl;
        auto p1 = Make_MyShared<MyPoint>(3, 4);
        cout << "p1 use count: " << p1.use_count() << endl;
        
        auto p2 = p1; // Копирование разрешено
        cout << "p1 use count: " << p1.use_count() << endl;
        cout << "p2 use count: " << p2.use_count() << endl;
        
        p1->print();
        p2->print();
        
        auto p3 = move(p2); // Перемещение
        cout << "After move:" << endl;
        cout << "p1 use count: " << p1.use_count() << endl;
        cout << "p2 use count: " << p2.use_count() << endl;
        cout << "p3 use count: " << p3.use_count() << endl;
    }
    
    return 0;
}