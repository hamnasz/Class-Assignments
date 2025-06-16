#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> actions;
    string command, text;

    while (true) {
        cout << "\nEnter command (type, undo, exit): ";
        cin >> command;

        if (command == "type") {
            cout << "Enter text: ";
            cin.ignore();  // Ignore the newline from previous input
            getline(cin, text);
            actions.push(text);
            cout << "Typed: \"" << text << "\"" << endl;
        } 
        else if (command == "undo") {
            if (actions.empty()) {
                cout << "Nothing to undo." << endl;
            } else {
                cout << "Undoing last action: \"" << actions.top() << "\"" << endl;
                actions.pop();
            }
        } 
        else if (command == "exit") {
            break;
        } 
        else {
            cout << "Invalid command. Try 'type', 'undo', or 'exit'." << endl;
        }
        
        // Display the current content
        cout << "\nCurrent text content: ";
        if (actions.empty()) {
            cout << "[Empty]" << endl;
        } else {
            stack<string> temp = actions;
            string output;
            while (!temp.empty()) {
                output = temp.top() + " " + output;
                temp.pop();
            }
            cout << output << endl;
        }
    }

    return 0;
}

