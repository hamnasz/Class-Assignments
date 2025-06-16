//5. Undo Function
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> actions;
    int choice;
    string action;

    do {
        cout << "1. Perform action\n2. Undo\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "Enter action: ";
            cin.ignore();
            getline(cin, action);
            actions.push(action);
        } else if (choice == 2 && !actions.empty()) {
            cout << "Undoing action: " << actions.top() << endl;
            actions.pop();
        }
    } while (choice != 3);
    return 0;
}