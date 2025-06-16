#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void printList(const vector<string>& students) {
    if (students.empty()) {
        cout << "No students in the list." <<endl;
        return;
    }

    cout << "Student List:" <<endl;
    for (const auto& name : students) {
        cout << "- " << name <<endl;
    }
}

int main() {
    vector<string> students;
    string command, name;

    while (true) {
        cout << "\nCommands: add <name>, remove <name>, display, exit" <<endl;
        cout << "Enter command: ";
        getline(cin, command);

        if (command.substr(0, 4) == "add ") {
            name = command.substr(4);
            students.push_back(name);
            sort(students.begin(), students.end()); 
            cout << "Added: " << name <<endl;
        } else if (command.substr(0, 7) == "remove ") {
            name = command.substr(7);
            auto it = remove(students.begin(), students.end(), name);
            if (it != students.end()) {
                students.erase(it, students.end());
                cout << "Removed: " << name <<endl;
            } else {
                cout << "Student not found: " << name <<endl;
            }
        } else if (command == "display") {
            printList(students);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command. Please try again." <<endl;
        }
    }

    return 0;
}
