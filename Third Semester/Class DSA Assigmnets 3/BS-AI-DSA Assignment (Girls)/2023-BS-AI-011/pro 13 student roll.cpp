//student roll call
#include <iostream>
#include <list>

using namespace std;

bool compareNames(const string& a, const string& b) {
    return a < b;
}

int main() {
    list<string> students;
    int choice;

    while (true) {
        cout << "1. Add student\n2. Remove student\n3. Display students\n4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                cout << "Enter student name: ";
                cin >> name;
                students.push_back(name);
                students.sort(compareNames);
                break;
            }
            case 2: {
                if (students.empty()) {
                    cout << "No students to remove.\n";
                } else {
                    students.pop_back();
                    cout << "Last student removed.\n";
                }
                break;
            }
            case 3: {
                if (students.empty()) {
                    cout << "No students to display.\n";
                } else {
                    cout << "Students:\n";
                    for (const string& name : students) {
                        cout << "- " << name << endl;
                    }
                }
                break;
            }
            case 4:
                exit(0);
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}