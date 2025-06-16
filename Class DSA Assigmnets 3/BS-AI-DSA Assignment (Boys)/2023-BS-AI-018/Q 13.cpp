#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Function to display the menu
void displayMenu() {
    cout << "\nStudent Name Management System\n";
    cout << "--------------------------------\n";
    cout << "1. Add Student Name\n";
    cout << "2. Remove Student Name\n";
    cout << "3. Display Student Names\n";
    cout << "4. Exit\n";
    cout << "--------------------------------\n";
    cout << "Enter your choice: ";
}

// Function to add student name
void addStudent(vector<string>& studentList) {
    string name;
    cout << "Enter student name: ";
    getline(cin, name);
    studentList.push_back(name);
    cout << "Student name added successfully.\n";
}

// Function to remove student name
void removeStudent(vector<string>& studentList) {
    string name;
    cout << "Enter student name to remove: ";
    getline(cin, name);
    for (auto it = studentList.begin(); it != studentList.end(); ++it) {
        if (*it == name) {
            studentList.erase(it);
            cout << "Student name removed successfully.\n";
            return;
        }
    }
    cout << "Student name not found.\n";
}

// Function to display student names
void displayStudents(const vector<string>& studentList) {
    if (studentList.empty()) {
        cout << "No student names in the list.\n";
        return;
    }
    cout << "Student Names (in alphabetical order):\n";
    for (const auto& name : studentList) {
        cout << name << endl;
    }
}

int main() {
    vector<string> studentList;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Ignore newline character left in input buffer

        switch (choice) {
            case 1:
                addStudent(studentList);
                sort(studentList.begin(), studentList.end());
                break;
            case 2:
                removeStudent(studentList);
                break;
            case 3:
                sort(studentList.begin(), studentList.end());
                displayStudents(studentList);
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please choose again.\n";
        }
    }

    return 0;
}

