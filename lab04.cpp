#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <fstream>
#include <string>

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
};

class Manager : public Employee {
    double managerBonusPercent;
    std::string departmentName;

public:
    Manager(const std::string& name, double sal, double expBonus, int expYears,
            double mgrBonus, const std::string& dept)
        : Employee(name, sal, expBonus, expYears), managerBonusPercent(mgrBonus), departmentName(dept) {}

    double calculateSalary() const override {
        double baseSalary = Employee::calculateSalary();
        return baseSalary + (baseSalary * managerBonusPercent / 100.0);
    }

    void print() const override {
        Employee::print();
        std::cout << "Надбавка за руководство (%): " << managerBonusPercent << std::endl;
        std::cout << "Подразделение: " << departmentName << std::endl;
        std::cout << "Итоговая зарплата с учетом надбавки: " << calculateSalary() << std::endl;
    }
};

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
        } else if (type == "Manager") {
            inFile >> std::ws;
            std::getline(inFile, name);
            inFile >> salary >> expBonus >> expYears >> mgrBonus >> std::ws;
            std::getline(inFile, dept);
            employees.emplace_back(Manager(name, salary, expBonus, expYears, mgrBonus, dept));
        }
    }
    return employees;
}

void writeToFile(const std::string& filename, const std::vector<Employee>& employees) {
    std::ofstream outFile(filename);
    for (const auto& emp : employees) {
        outFile << emp << "\n\n";
    }
}

int main() {
    std::vector<Employee> employees = readEmployeesFromFile("input.txt");
    std::list<Employee> employeeList(employees.begin(), employees.end());
    std::deque<Employee> employeeDeque(employees.begin(), employees.end());

    std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.getSalary() > b.getSalary();
    });

    employeeList.sort([](const Employee& a, const Employee& b) {
        return a.getFullName() < b.getFullName();
    });

    writeToFile("output.txt", employees);

    return 0;
}