#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> actions;
    string action, command;

    while (true) {
        cout << "Enter command (add/undo/exit): ";
        cin >> command;
        if (command == "add") {
            cout << "Enter action: ";
            cin.ignore();
            getline(cin, action);
            actions.push(action);
        } else if (command == "undo") {
            if (!actions.empty()) {
                cout << "Undo action: " << actions.top() << endl;
                actions.pop();
            } else {
                cout << "No actions to undo." << endl;
            }
        } else if (command == "exit") break;
    }
    return 0;
}
