
#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include "Student.h"
#include "SLL1.h"
#include "stack1.h"
using namespace std;

struct UndoAction {
    bool wasAdd;
    Student student;
};

class StudentManager {
private:
    SinglyLinkedList<Student> students;
    Stack<UndoAction> undoStack;

public:
    bool AddStudent(const Student& s, bool recordUndo = true) {
        Student existing{};

        if (students.GetByRoll(s.roll, existing)) {
            cout << "Error: A student with roll number "
                 << s.roll << " already exists.\n";
            return false;
        }

        students.AddAtTheEnd(s);

        if (recordUndo) {
            undoStack.Push(UndoAction{true, s});
        }

        cout << "Student added successfully.\n";
        return true;
    }

    void DisplayAll() const {
        students.PrintAll();
    }

    void SearchStudent(int roll) const {
        Student found{};

        if (students.GetByRoll(roll, found)) {
            cout << found << '\n';
        } else {
            cout << "Student with roll number "
                 << roll << " not found.\n";
        }
    }

    bool RemoveStudent(int roll, bool recordUndo = true) {
        Student found{};

        if (!students.GetByRoll(roll, found)) {
            cout << "Student with roll number "
                 << roll << " not found.\n";
            return false;
        }

        if (students.Remove(found)) {
            if (recordUndo) {
                undoStack.Push(UndoAction{false, found});
            }

            cout << "Student removed successfully.\n";
            return true;
        }

        cout << "Unable to remove student.\n";
        return false;
    }

    void UndoLastAction() {
        if (undoStack.IsEmpty()) {
            cout << "Nothing to undo.\n";
            return;
        }

        UndoAction action = undoStack.Pop();

        if (action.wasAdd) {
            students.Remove(action.student);
            cout << "Undo successful: last addition was reversed.\n";
        } else {
            Student existing{};

            if (!students.GetByRoll(action.student.roll, existing)) {
                students.AddAtTheEnd(action.student);
                cout << "Undo successful: removed student was restored.\n";
            } else {
                cout << "Undo failed: that roll number already exists.\n";
            }
        }
    }

    bool SaveToFile(const string& filename = "students.txt") const {
        ofstream out(filename);

        if (!out) {
            cout << "Error: Could not open file for saving.\n";
            return false;
        }

        // Save records: O(n) time, O(1) auxiliary space.
        students.ForEach([&out](const Student& s) {
            out << s.roll << '|'
                << s.marks << '|'
                << s.name << '\n';
        });

        if (!out) {
            cout << "Error while writing to file.\n";
            return false;
        }

        cout << "Records saved to " << filename << ".\n";
        return true;
    }

    bool LoadFromFile(const string& filename = "students.txt") {
        ifstream in(filename);

        if (!in) {
            cout << "Error: Could not open " << filename << ".\n";
            return false;
        }

        SinglyLinkedList<Student> loaded;
        string line;
        int loadedCount = 0;

        // Read records: O(n) in file size, excluding duplicate checks.
        while (getline(in, line)) {
            size_t first = line.find('|');
            size_t second = (first == string::npos)
                                ? string::npos
                                : line.find('|', first + 1);

            if (first == string::npos || second == string::npos) {
                continue;
            }

            try {
                Student s;
                s.roll = stoi(line.substr(0, first));
                s.marks = stof(line.substr(first + 1, second - first - 1));
                s.name = line.substr(second + 1);

                Student duplicate{};

                if (!loaded.GetByRoll(s.roll, duplicate)) {
                    loaded.AddAtTheEnd(s);
                    ++loadedCount;
                }
            } catch (...) {
                // Skip malformed records.
            }
        }

        students.Clear();

        loaded.ForEach([this](const Student& s) {
            students.AddAtTheEnd(s);
        });

        while (!undoStack.IsEmpty()) {
            undoStack.Pop();
        }

        cout << "Loaded " << loadedCount
             << " student record(s) from " << filename << ".\n";

        return true;
    }

    void ShowComplexityReport() const {
        cout << "\n--- Operation Complexity Report ---\n";
        cout << "Add at end      | Singly Linked List | O(1) | O(1)\n";
        cout << "Search by roll  | Singly Linked List | O(n) | O(1)\n";
        cout << "Remove by roll  | Singly Linked List | O(n) | O(1)\n";
        cout << "Display all     | Singly Linked List | O(n) | O(1)\n";
        cout << "Undo push       | Stack               | O(1) | O(1)\n";
        cout << "Undo pop        | Stack               | O(1) | O(1)\n";
    }
};

#endif