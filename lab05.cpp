#include <iostream>
#include <set>
#include <unordered_set>
#include <fstream>
#include <string>
#include <functional>

class Employee {
protected:
    std::string fullName;
    double salary;
    double experienceBonusPercent;
    int experienceYears;

public:
    Employee(const std::string& name, double sal, double bonus, int exp)
        : fullName(name), salary(sal), experienceBonusPercent(bonus), experienceYears(exp) {}

    virtual double calculateSalary() const {
        return salary + (salary * experienceBonusPercent * experienceYears / 100.0);
    }

    virtual void print() const {
        std::cout << "ФИО: " << fullName << std::endl;
        std::cout << "Оклад: " << salary << std::endl;
        std::cout << "Надбавка за стаж (% за год): " << experienceBonusPercent << std::endl;
        std::cout << "Стаж (лет): " << experienceYears << std::endl;
        std::cout << "Итоговая зарплата: " << calculateSalary() << std::endl;
    }

    std::string getFullName() const { return fullName; }
    double getSalary() const { return salary; }

    friend std::ostream& operator<<(std::ostream& os, const Employee& emp) {
        emp.print();
        return os;
    }

    bool operator<(const Employee& other) const {
        return fullName < other.fullName;
    }

    bool operator==(const Employee& other) const {
        return fullName == other.fullName;
    }
};

namespace std {
    template<>
    struct hash<Employee> {
        size_t operator()(const Employee& emp) const {
            return hash<std::string>()(emp.getFullName());
        }
    };
}

std::vector<Employee> readEmployeesFromFile(const std::string& filename) {
    std::vector<Employee> employees;
    std::ifstream inFile(filename);
    
    if (!inFile) return employees;

    std::string type, name, dept;
    double salary, expBonus, mgrBonus;
    int expYears;

    while (inFile >> type) {
        if (type == "Employee") {
            inFile >> std::ws;
            std::getline(inFile, name);
            inFile >> salary >> expBonus >> expYears;
            employees.emplace_back(name, salary, expBonus, expYears);
        }
    }
    return employees;
}

int main() {
    std::vector<Employee> employees = readEmployeesFromFile("input.txt");
    std::set<Employee> employeeSet(employees.begin(), employees.end());
    std::unordered_set<Employee> employeeUnorderedSet(employees.begin(), employees.end());

    for (const auto& emp : employeeSet) {
        std::cout << emp << std::endl;
    }

    for (const auto& emp : employeeUnorderedSet) {
        std::cout << emp << std::endl;
    }

    return 0;
}