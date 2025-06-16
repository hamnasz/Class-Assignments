#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class StudentList {
private:
    vector<string> names;
public:
    void addName(const string& name) {
        names.push_back(name);
        cout << name << " has been added to the list." << endl;
    }
    void removeName(const string& name) {
        auto it = find(names.begin(), names.end(), name);
        if (it != names.end()) {
            names.erase(it);
            cout << name << " has been removed from the list." << endl;
        } else {
            cout << name << " not found in the list." << endl;
        }
    }
    void printNames() {
        if (names.empty()) {
            cout << "The student list is empty." << endl;
            return;
        }

        sort(names.begin(), names.end()); 
        cout << "Student List:" << endl;
        for (const string& name : names) {
            cout << "- " << name << endl;
        }
    }
};

int main() {
    StudentList studentList;
    string command, name;

    while (true) {
        cout << "\nEnter command (add/remove/display/exit): ";
        cin >> command;

        if (command == "add") {
            cout << "Enter student name to add: ";
            cin.ignore(); // Clear the newline
            getline(cin, name);
            studentList.addName(name);
        } 
        else if (command == "remove") {
            cout << "Enter student name to remove: ";
            cin.ignore(); // Clear the newline
            getline(cin, name);
            studentList.removeName(name);
        } 
        else if (command == "display") {
            studentList.printNames();
        } 
        else if (command == "exit") {
            cout << "Exiting program." << endl;
            break;
        } 
        else {
            cout << "Invalid command. Please enter 'add', 'remove', 'display', or 'exit'." << endl;
        }
    }

    return 0;
}