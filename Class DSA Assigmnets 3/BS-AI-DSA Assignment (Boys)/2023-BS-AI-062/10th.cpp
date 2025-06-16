#include <iostream>
#include <stack>
#include <string>
using namespace std;

class TextEditor {
private:
    stack<string> actions;
    string text;

public:
    void type(const string &input) {
        actions.push(input);
        text += input;
    }

    void undo() {
        if (!actions.empty()) {
            string lastAction = actions.top();
            text.erase(text.size() - lastAction.size());
            actions.pop();
        }
    }

    void display() {
        cout << "Current text: " << text << "\n";
    }
};

int main() {
    TextEditor editor;
    int choice;
    string input;

    do {
        cout << "1. Type\n2. Undo\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter text to type: ";
                cin.ignore();
                getline(cin, input);
                editor.type(input);
                break;
            case 2:
                editor.undo();
                break;
            case 3:
                editor.display();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while (choice != 4);

    return 0;
}
