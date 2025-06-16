#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

int main() {
    list<string> studentList;
    string name;
    int choice;

    do {
        cout << "1. Add Student\n2. Remove Student\n3. Display Students\n4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter student name: ";
            cin >> name;
            studentList.push_back(name);
            studentList.sort(); // Sort the list alphabetically
        } else if (choice == 2) {
            cout << "Enter student name to remove: ";
            cin >> name;
            studentList.remove(name);
        } else if (choice == 3) {
            cout << "Student List:\n";
            for (const string &student : studentList) {
                cout << student << endl;
            }
        }
    } while (choice != 4);

    return 0;
}
