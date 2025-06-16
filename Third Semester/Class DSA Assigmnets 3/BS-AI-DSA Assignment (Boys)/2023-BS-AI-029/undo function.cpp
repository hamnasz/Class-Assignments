#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> actions; // Stack to hold the text actions
    string currentText;    // Variable to hold the current text
    string input;          // Variable to store user input
    char choice;          // Variable to store user choice

    while (true) {
        cout << "Current Text: " << currentText << endl;
        cout << "Options: \n";
        cout << "1. Add text\n";
        cout << "2. Undo\n";
        cout << "3. Exit\n";
        cout << "Choose an option (1-3): ";
        cin >> choice;

        // Clear input buffer for getline
        cin.ignore();

        if (choice == '1') {
            cout << "Enter text to add: ";
            getline(cin, input);

            // Push the current text to the stack before adding new text
            actions.push(currentText);
            currentText += input; // Append new text
        } 
        else if (choice == '2') {
            if (!actions.empty()) {
                // Pop the last action from the stack
                currentText = actions.top();
                actions.pop();
            } else {
                cout << "No actions to undo." << endl;
            }
        } 
        else if (choice == '3') {
            cout << "Exiting the text editor." << endl;
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
        cout << endl; // For better readability
    }

    return 0;
}
