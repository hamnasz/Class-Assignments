#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> history;       // Stack to store the history of text states
    string text = "";            // Current state of the text
    string command;

    while (true) {
        cout << "\nCurrent Text: \"" << text << "\"" << endl;
        cout << "Enter a command (append <text>, undo, exit): ";
        getline(cin, command);

        // Check if the command starts with "append "
        if (command.find("append ") == 0) {
            // Push the current text state to the stack before appending
            history.push(text);

            // Extract the text to append
            string newText = command.substr(7);
            text += newText; // Append the new text to the current text
            cout << "Text after append: \"" << text << "\"" << endl;
        } 
        // Check for the "undo" command
        else if (command == "undo") {
            // If history is not empty, undo the last action
            if (!history.empty()) {
                text = history.top(); // Revert to the last saved state
                history.pop();        // Remove it from the history
                cout << "Undo performed. Current text: \"" << text << "\"" << endl;
            } else {
                cout << "Nothing to undo." << endl;
            }
        } 
        // Check for the "exit" command
        else if (command == "exit") {
            cout << "Exiting the text editor." << endl;
            break;
        } 
        // Handle invalid commands
        else {
            cout << "Invalid command. Please use 'append <text>', 'undo', or 'exit'." << endl;
        }
    }

    return 0;
}
