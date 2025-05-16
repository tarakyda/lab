#include <iostream>
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

    virtual ~Employee() {}
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