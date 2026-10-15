#include <iostream>
#include <limits>
#include <string>
#include "StudentManager.h"
using namespace std;

int ReadInt(const string& prompt) {
    int value;

    // Input validation: repeats until a valid integer is entered.
    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Please enter a valid whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float ReadFloat(const string& prompt) {
    float value;

    // Input validation: repeats until a valid number is entered.
    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Please enter valid marks.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n===== STUDENT RECORD MANAGER =====\n";
        cout << "1. Add student\n";
        cout << "2. Display all students\n";
        cout << "3. Search student by roll\n";
        cout << "4. Remove student by roll\n";
        cout << "5. Undo last add / remove\n";
        cout << "6. Save to file\n";
        cout << "7. Load from file\n";
        cout << "8. Show operation complexity report\n";
        cout << "9. Exit\n";

        choice = ReadInt("Enter your choice: ");

        switch (choice) {
        case 1: {
            Student s;

            s.roll = ReadInt("Enter roll number: ");

            cout << "Enter student name: ";
            getline(cin, s.name);

            s.marks = ReadFloat("Enter marks: ");

            manager.AddStudent(s);
            break;
        }

        case 2:
            manager.DisplayAll();
            break;

        case 3:
            manager.SearchStudent(
                ReadInt("Enter roll number to search: "));
            break;

        case 4:
            manager.RemoveStudent(
                ReadInt("Enter roll number to remove: "));
            break;

        case 5:
            manager.UndoLastAction();
            break;

        case 6:
            manager.SaveToFile();
            break;

        case 7:
            manager.LoadFromFile();
            break;

        case 8:
            manager.ShowComplexityReport();
            break;

        case 9:
            cout << "Exiting Student Record Manager. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please select 1 to 9.\n";
        }

    } while (choice != 9); // Repeat the menu until Exit is selected.

    return 0;
}