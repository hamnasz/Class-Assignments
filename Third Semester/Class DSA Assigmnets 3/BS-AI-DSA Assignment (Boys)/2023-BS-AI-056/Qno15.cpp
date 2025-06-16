#include <iostream>
#include <stack>
#include <string>

using namespace std;

void displayMenu() {
    cout << "\nText Editor Menu:" << endl;
    cout << "1. Type text" << endl;
    cout << "2. Undo last action" << endl;
    cout << "3. Display current text" << endl;
    cout << "4. Exit" << endl;
}

int main() {
    stack<string> actions;
    string currentText;
    int choice;

    do {
        displayMenu();
        cout << "Choose an option (1-4): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string inputText;
                cout << "Enter text to type: ";
                getline(cin, inputText);
                actions.push(currentText);
                currentText += inputText;
                cout << "Text added." << endl;
                break;
            }

            case 2:
                if (!actions.empty()) {
                    currentText = actions.top();
                    actions.pop();
                    cout << "Last action undone." << endl;
                } else {
                    cout << "No actions to undo." << endl;
                }
                break;

            case 3:
                cout << "Current text: \"" << currentText << "\"" << endl;
                break;

            case 4:
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
