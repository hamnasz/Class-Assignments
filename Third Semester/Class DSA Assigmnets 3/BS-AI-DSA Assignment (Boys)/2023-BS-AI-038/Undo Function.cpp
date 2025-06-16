#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> actions;
    string currentText = "";
    
    while (true) {
        cout << "Current text: " << currentText << endl;
        cout << "1. Type new text\n2. Undo\n3. Quit" << endl;
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            string newText;
            cout << "Enter new text: ";
            cin >> newText;
            actions.push(currentText);
            currentText += newText;
        } else if (choice == 2) {
            if (!actions.empty()) {
                currentText = actions.top();
                actions.pop();
            } else {
                cout << "No previous action." << endl;
            }
        } else if (choice == 3) {
            break;
        }
    }
    return 0;
}