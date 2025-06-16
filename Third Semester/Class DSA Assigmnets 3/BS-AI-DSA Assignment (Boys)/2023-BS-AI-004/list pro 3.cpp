#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main() {
    list<string> students;
    int choice;
    string name;

    do {
        cout << "1. Add student\n2. Remove student\n3. Show list\n4. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter student name: ";
            cin >> name;
            students.push_back(name);
        } else if (choice == 2) {
            cout << "Enter student name to remove: ";
            cin >> name;
            students.remove(name);
        } else if (choice == 3) {
            students.sort();
            cout << "Student List:\n";
            for (const string &s : students) cout << s << endl;
        }
    } while (choice != 4);
    return 0;
}
