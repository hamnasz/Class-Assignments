#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    list<string> studentNames;
    string action, name;
    while (true) {
        cout << "Choose an action (add/remove/show/sort/quit): ";
        cin >> action;

        if (action == "add") {
            cout << "Enter the name of the student to add: ";
            cin >> name;
            studentNames.push_back(name);
        } else if (action == "remove") {
            cout << "Enter the name of the student to remove: ";
            cin >> name;
            studentNames.remove(name);
        } else if (action == "show") {
            cout << "List of Students: ";
            for (const auto &name : studentNames) cout << name << " ";
            cout << endl;
        } else if (action == "sort") {
            vector<string> tempVector(studentNames.begin(), studentNames.end());
            sort(tempVector.begin(), tempVector.end());
            cout << "Sorted List of Students: ";
            for (const auto &name : tempVector) cout << name << " ";
            cout << endl;
        } else if (action == "quit") {
            break;
        } else {
            cout << "Invalid action. Please try again." << endl;
        }
    }

    return 0;
}
