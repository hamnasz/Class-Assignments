#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    list<string> studentList;
    string name;
    int choice;

    do {
        cout << "1. Add student\n";
        cout << "2. Remove student\n";
        cout << "3. Display students\n";
        cout << " 4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter student name: ";
                cin >> name;
                studentList.push_back(name);
                break;
            case 2:
                cout << "Enter student name to remove: ";
                cin >> name;
                studentList.remove(name);
                break;
            case 3:
                studentList.sort(); // Sort the list alphabetically
                cout << "Current student list:\n";
                for (const auto& n : studentList) {
                    cout << n << " ";
                }
                cout << endl;
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
