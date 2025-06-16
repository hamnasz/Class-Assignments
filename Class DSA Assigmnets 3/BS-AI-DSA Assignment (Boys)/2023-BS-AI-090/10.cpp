#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> actions;
    string command, action;

    while (true) {
        cout << "Enter command (do <action> / undo / exit): ";
        cin >> command;

        if (command == "do") {
            cin >> action;
            actions.push(action);
            cout << "Action performed: " << action << endl;
        } else if (command == "undo") {
            if (!actions.empty()) {
                cout << "Undoing action: " << actions.top() << endl;
                actions.pop();
            } else {
                cout << "No actions to undo." << endl;
            }
        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}
