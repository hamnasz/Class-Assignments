#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class StudentList {
private:
    vector<string> students;  // Vector to store student names

public:
    // Add a student name to the list
    void addStudent(const string& name) {
        students.push_back(name);
        sort(students.begin(), students.end());  // Sort the list after adding
        cout << name << " added to the student list.\n";
    }

    // Remove a student name from the list
    void removeStudent(const string& name) {
        auto it = find(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
            cout << name << " removed from the student list.\n";
        } else {
            cout << name << " not found in the student list.\n";
        }
    }

    // Display all student names in alphabetical order
    void displayStudents() const {
        if (students.empty()) {
            cout << "The student list is empty.\n";
            return;
        }

        cout << "Current student list in alphabetical order:\n";
        for (const auto& name : students) {
            cout << "- " << name << endl;
        }
    }
};

int main() {
    StudentList studentList;
    int choice;
    string name;

    do {
        cout << "\nStudent Management Menu:\n";
        cout << "1. Add student\n";
        cout << "2. Remove student\n";
        cout << "3. Display student list\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline from the input buffer

        switch (choice) {
            case 1:
                cout << "Enter student name to add: ";
                getline(cin, name);
                studentList.addStudent(name);
                break;

            case 2:
                cout << "Enter student name to remove: ";
                getline(cin, name);
                studentList.removeStudent(name);
                break;

            case 3:
                studentList.displayStudents();
                break;

            case 4:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

