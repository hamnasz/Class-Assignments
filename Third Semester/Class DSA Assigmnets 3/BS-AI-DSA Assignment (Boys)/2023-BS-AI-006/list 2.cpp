#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class StudentList {
private:
    vector<string> names; // Vector to store student names

public:
    // Function to add a student name
    void addStudent(const string& name) {
        names.push_back(name);
        cout << name << " has been added to the list." << endl;
    }

    // Function to remove a student name
    void removeStudent(const string& name) {
        auto it = find(names.begin(), names.end(), name);
        if (it != names.end()) {
            names.erase(it);
            cout << name << " has been removed from the list." << endl;
        } else {
            cout << name << " not found in the list." << endl;
        }
    }

    // Function to display the list of names in alphabetical order
    void displayStudents() {
        if (names.empty()) {
            cout << "No students in the list." << endl;
            return;
        }

        // Sort names alphabetically
        sort(names.begin(), names.end());

        cout << "Student List (in alphabetical order):" << endl;
        for (const string& name : names) {
            cout << "- " << name << endl;
        }
    }
};

int main() {
    StudentList studentList;
    int choice;
    string name;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Display Students\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore(); // Clear newline character from input buffer

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
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
