#include <iostream>
#include <string>
#include <algorithm> // For sorting
using namespace std;

const int MAX_STUDENTS = 100;
string students[MAX_STUDENTS];
int studentCount = 0;  // Keeps track of the number of students

void addStudent(const string& name) {
    if (studentCount < MAX_STUDENTS) {
        students[studentCount++] = name;
        cout << "Student \"" << name << "\" added.\n";
    } else {
        cout << "Student list is full.\n";
    }
}

void removeStudent(const string& name) {
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i] == name) {
            found = true;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Student \"" << name << "\" removed.\n";
            break;
        }
    }
    if (!found) {
        cout << "Student \"" << name << "\" not found.\n";
    }
}

void displayStudents() {
    if (studentCount == 0) {
        cout << "No students to display.\n";
        return;
    }

    // Sort the student names in alphabetical order
    sort(students, students + studentCount);

    cout << "\nStudent List (Alphabetical Order):\n";
    for (int i = 0; i < studentCount; i++) {
        cout << "- " << students[i] << endl;
    }
}

int main() {
    int choice;
    string name;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1. Add student\n";
        cout << "2. Remove student\n";
        cout << "3. Display students\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter student name to add: ";
                getline(cin, name);
                addStudent(name);
                break;
            case 2:
                cout << "Enter student name to remove: ";
                getline(cin, name);
                removeStudent(name);
                break;
            case 3:
                displayStudents();
                break;
            case 4:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid option. Please choose again.\n";
                break;
        }
    }
}