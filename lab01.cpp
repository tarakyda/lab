#include <iostream>
#include <vector>﻿
#include <algorithm>

using namespace std;

float mean(vector<unsigned> r) {
    int sum = 0;
    for (auto i : r) {
        sum += i;
    }
    return sum / r.size();
}

struct Student
{
    string Name;
    string GroupId;
    vector<unsigned> Ratings;
    vector<string> Subjects;
};

class Group {
private:

    vector<Student> students = {};

public:
    
    void add(Student s) {
        students.push_back(s);
    }
    void add(vector<Student>& s) {
        for (Student i : s) {
            students.push_back(i);
        }
    }
    void show() {
        for (auto i : students) {
            cout << i.Name << endl;
            cout << i.GroupId << endl;
            for (int j = 0; j < i.Ratings.size(); j++) {
                cout << i.Ratings[j] << " - " << i.Subjects[j] << endl;
            }
            cout << endl;
        }
    }

    void sort_by_name() {
        sort(students.begin(), students.end(), [](Student& a, Student& b){ return a.Name < b.Name; } );
    }

    void sort_by_ratings(){
        sort(students.begin(), students.end(), [](Student a, Student b) { return mean(a.Ratings) < mean(b.Ratings); });
    }

    size_t CountExcellent() {
        size_t exc = 0;
        for (auto st : students) {
            if (mean(st.Ratings) == 5) {
                exc++;
            }
        }
        return exc;
    }

    size_t CountTwoness() {
        size_t two = 0;
        for (auto st : students) {
            if (find(st.Ratings.begin(), st.Ratings.end(), 2) != st.Ratings.end()) {
                two++;
            }
        }
        return two;
    }

    vector<Student> VectorMathExcellent() {
        vector<Student> res;
        for (auto st : students) {
            for (int i = 0; i < st.Subjects.size(); i++) {
                if (st.Subjects[i] == "Math" && st.Ratings[i] == 5) {
                    res.push_back(st);
                }
            }
        }
        return res;
    }

    void del_by_name(string name) {
        for (vector<Student>::iterator iter = students.begin(); iter < students.end(); iter++) {
            if (iter->Name == name) {
                students.erase(iter);
                break;
            }
        }
    }

    void search(string name) {
        for (vector<Student>::iterator iter = students.begin(); iter < students.end(); iter++) {
            if (iter->Name == name) {
                cout << iter->Name << endl;
                cout << iter->GroupId << endl;
                for (int j = 0; j < iter->Ratings.size(); j++) {
                    cout << iter->Ratings[j] << " - " << iter->Subjects[j] << endl;
                }
                cout << endl;
            }
        }
    }
    void search(vector<unsigned> v) {
        for (vector<Student>::iterator iter = students.begin(); iter < students.end(); iter++) {
            if (iter->Ratings == v) {
                cout << iter->Name << endl;
                cout << iter->GroupId << endl;
                for (int j = 0; j < iter->Ratings.size(); j++) {
                    cout << iter->Ratings[j] << " - " << iter->Subjects[j] << endl;
                }
                cout << endl;
            }
        }
    }
};


int main()
{
    vector<Student> students = {
     {"Ivan", "Group1", {5, 5}, {"Math", "Physics"}},
     {"Oleg", "Group2", {5, 5}, {"Math", "Physics"}},
     {"Sergey", "Group3", {4, 5}, {"Math", "Physics"}},
     {"Leonid", "Group3", {5, 2}, {"Math", "Physics"}}
    };

    Group a;
    a.add(students);
    vector<unsigned> vec = { 2,2 };
    a.search(vec);
}

