#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> actions;
    string action;
    int choice;

    do {
        cout << "1. Perform Action\n2. Undo Last Action\n3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter action: ";
            cin >> action;
            actions.push(action);
            cout << "Performed action: " << action << endl;
        } else if (choice == 2) {
            if (!actions.empty()) {
                cout << "Undoing action: " << actions.top() << endl;
                actions.pop();
            } else {
                cout << "No actions to undo." << endl;
            }
        }
    } while (choice != 3);

    return 0;
}
