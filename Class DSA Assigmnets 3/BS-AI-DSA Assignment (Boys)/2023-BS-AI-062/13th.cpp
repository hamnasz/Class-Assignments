#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class StudentList {
private:
    vector<string> students;

public:
    void addStudent(const string& name) {
        students.push_back(name);
        sort(students.begin(), students.end());
    }

    void removeStudent(const string& name) {
        auto it = find(students.begin(), students.end(), name);
        if (it != students.end()) {
            students.erase(it);
            sort(students.begin(), students.end());
        } else {
            cout << "Student not found.\n";
        }
    }

    void printList() const {
        for (const auto& name : students) {
            cout << name << "\n";
        }
    }
};

int main() {
    StudentList studentList;
    int choice;
    string name;

    do {
        cout << "1. Add student\n2. Remove student\n3. Print list\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter student's name to add: ";
                cin.ignore();
                getline(cin, name);
                studentList.addStudent(name);
                break;
            case 2:
                cout << "Enter student's name to remove: ";
                cin.ignore();
                getline(cin, name);
                studentList.removeStudent(name);
                break;
            case 3:
                studentList.printList();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
