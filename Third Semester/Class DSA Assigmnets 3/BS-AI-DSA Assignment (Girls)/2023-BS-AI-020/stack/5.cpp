#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> actions;
    string action;
    string choice;

    while (true) {
        cout << "Enter an action (or 'undo' to undo last action): ";
        cin >> choice;

        if (choice == "undo") {
            if (actions.empty()) {
                cout << "No actions to undo." << endl;
            } else {
                action = actions.top();
                actions.pop();
                cout << "Undid action: " << action << endl;
            }
        } else {
            actions.push(choice); // Push the action onto the stack
            cout << "Performed action: " << choice << endl;
        }
    }

    return 0;
}
