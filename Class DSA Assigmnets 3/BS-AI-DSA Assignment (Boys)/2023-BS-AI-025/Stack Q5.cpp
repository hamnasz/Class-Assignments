#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> commandStack;
    string choice;

    while (true) {
        cout << "Enter your choice (add, undo, exit): ";
        cin >> choice;

        if (choice == "add") {
            string addText;
            cout << "Enter the text you want to add: ";
            cin.ignore(); 
            cin>>addText; 
            commandStack.push(addText);
            cout << "Text added.\n";

        } else if (choice == "undo") {
            if (!commandStack.empty()) {
                cout << "Undoing last text: " << commandStack.top() << endl;
                commandStack.pop();
            } else {
                cout << "No text to undo.\n";
            }

        } else if (choice == "exit") {
            break;

        } else {
            cout << "Invalid choice. Please enter 'add', 'undo', or 'exit'.\n";
        }
    }

    return 0;
}
