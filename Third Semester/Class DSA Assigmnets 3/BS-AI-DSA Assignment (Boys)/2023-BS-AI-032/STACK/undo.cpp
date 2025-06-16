#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> actions;
    string currentText;
    string command;

    while (true) {
        cout << "Current text: " << currentText << endl;
        cout << "Enter a command (type <text>, undo, exit): ";
        getline(cin, command);

        if (command.find("type ") == 0) {
            string textToType = command.substr(5); // Get the text after "type "
            actions.push(currentText); // Save the current state before updating
            currentText += textToType;  // Update the current text
        } else if (command == "undo") {
            if (!actions.empty()) {
                currentText = actions.top(); // Restore the last action
                actions.pop();
                cout << "Undo successful." << endl;
            } else {
                cout << "No actions to undo." << endl;
            }
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command." << endl;
        }
    }

    cout << "Final text: " << currentText << endl;
    return 0;
}
