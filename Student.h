#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

struct Student {
    int roll;
    float marks;
    string name;

    friend ostream& operator<<(ostream& out, const Student& s) {
        out << "Roll: " << s.roll
            << " | Name: " << s.name
            << " | Marks: " << s.marks;
        return out;
    }

    bool operator==(const Student& other) const {
        return roll == other.roll;
    }
};

#endif