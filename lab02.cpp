#include<iostream>
#include<cstring>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class String {
public:
    
    ~String() {
        delete[] Data;
    }

    String() {
        Data = new char[1];
        Data[0] = '\0';
    }

    // Конструктор копирования - создает копию строки other
    String(const String& other) {
        size_t len = strlen(other.Data);
        Data = new char[len + 1];
        strcpy_s(Data, len + 1 ,other.Data);
    }

    // Пользовательский конструктор - создает строку из C-style строки
    String(const char* data) {
        if (data == nullptr) {
            Data = new char[1];
            Data[0] = '\0';
        }
        else {
            size_t len = strlen(data);
            Data = new char[len + 1];
            strcpy_s (Data, len + 1, data);
        }
    }

    // Оператор присваивания - копирует содержимое other в текущий объект
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] Data;
            size_t len = std::strlen(other.Data);
            Data = new char[len + 1];
            strcpy_s(Data, len + 1, other.Data);
        }
        return *this;
    }

    // Оператор += - конкатенация строк
    String& operator+=(const String& other) {
        size_t len1 = strlen(Data);
        size_t len2 = strlen(other.Data);
        char* newData = new char[len1 + len2 + 1];
        strcpy_s(newData, len1 + len2 + 1, Data);
        strcat_s(newData, len1 + len2 + 1, Data);

        delete[] Data;
        Data = newData;
        return *this;
    }

    // Оператор *= - повторение строки m раз
    String& operator*=(unsigned int m) {
        size_t len = strlen(Data);
        char* newData = new char[len * m + 1];
        newData[0] = '\0';

        for (unsigned int i = 0; i < m; i++) {
            strcat_s(newData, len * m + 1 ,Data);
        }

        delete[] Data;
        Data = newData;
        return *this;
    }

    bool operator==(const String& rhs) const {
        return strcmp(Data, rhs.Data) == 0;
    }

    bool operator<(const String& rhs) const {
        return strcmp(Data, rhs.Data) < 0;
    }

    size_t Find(const String& substr) const {
        char* pos = strstr(Data, substr.Data);
        if (pos == nullptr) return -1;  // Подстрока не найдена
        return pos - Data;  // Возвращаем смещение от начала строки
    }

    void Replace(char oldSymbol, char newSymbol) {
        for (int i = 0; Data[i] != '\0'; i++) {
            if (Data[i] == oldSymbol) {
                Data[i] = newSymbol;
            }
        }
    }

    size_t Size() const {
        return strlen(Data);
    }

    bool Empty() const {
        return Data[0] == '\0';
    }

    char operator[](size_t index) const {
        return Data[index];
    }

    // Оператор [] для записи
    char& operator[](size_t index) {
        return Data[index];
    }

    void RTrim(char symbol) {
        size_t len = strlen(Data);
        while (len > 0 && Data[len - 1] == symbol) {
            Data[--len] = '\0';
        }
    }

    void LTrim(char symbol) {
        int start = 0;
        while (Data[start] == symbol) {
            start++;
        }
        if (start > 0) {
            size_t len = strlen(Data);
            for (int i = 0; i <= len - start; i++) {
                Data[i] = Data[i + start];
            }
        }
    }

    void swap(String& other) {
        char* temp = Data;
        Data = other.Data;
        other.Data = temp;
    }

    friend ostream& operator<<(std::ostream& out, const String& str) {
        out << str.Data;
        return out;
    }

private:
    char* Data;

    friend String operator+(const String& a, const String& b) {
        String result(a);
        result += b;
        return result;
    }

    friend String operator*(const String& a, unsigned int m) {
        String result(a);
        result *= m;
        return result;
    }

    bool operator!=(const String& rhs) const {
        return !(*this == rhs);
    }

    bool operator>(const String& rhs) const {
        return strcmp(Data, rhs.Data) > 0;
    }
};
int main() {

}