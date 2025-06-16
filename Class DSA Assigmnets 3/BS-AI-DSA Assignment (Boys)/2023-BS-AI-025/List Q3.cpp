#include <iostream>
#include <list>
#include <vector>
#include <algorithm> // Include for sort
using namespace std;

int main() {
    list<string> student;
    string choice, name;

    while (true) {
        cout << "Enter your choice (add/remove/display/sort/exit): ";
        cin >> choice;

        if (choice == "add") {
            cout << "Enter name of student to add: ";
            cin >> name;
            student.push_back(name);
        } else if (choice == "remove") {
            cout << "Enter name of student to remove: ";
            cin >> name;
            student.remove(name);
        } else if (choice == "display") {
            cout << "Students list: ";
            for (auto &name : student) cout << name << " ";
            cout << endl;
        } else if (choice == "sort") {
            vector<string> temp(student.begin(), student.end());
            sort(temp.begin(), temp.end());
            cout << "Sorted Students list: ";
            for (auto &name : temp) cout << name << " ";
            cout << endl;
        } else if (choice == "exit") {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
