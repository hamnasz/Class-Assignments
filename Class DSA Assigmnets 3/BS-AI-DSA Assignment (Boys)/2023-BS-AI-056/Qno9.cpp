#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<string> students;
    string command, name;

    while (true) {
        cout << "\nEnter command (add, remove, display, exit): ";
        cin >> command;

        if (command == "add") {
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            students.push_back(name);
            cout << name << " added.\n";
        } 
        else if (command == "remove") {
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            auto it = find(students.begin(), students.end(), name);
            if (it != students.end()) {
                students.erase(it);
                cout << name << " removed.\n";
            } else {
                cout << name << " not found.\n";
            }
        } 
        else if (command == "display") {
            if (students.empty()) {
                cout << "The list is empty.\n";
            } else {
                sort(students.begin(), students.end());
                cout << "Student list:\n";
                for (const string& student : students) {
                    cout << "- " << student << "\n";
                }
            }
        } 
        else if (command == "exit") {
            break;
        } 
        else {
            cout << "Invalid command.\n";
        }
    }
    return 0;
}
