#include <iostream>
#include <stack>
#include <string>
using namespace std;

class TextEditor {
private:
    stack<string> undoStack;
    string text;

public:
    void insert(const string& s) {
        undoStack.push(text);
        text += s;
    }

    void undo() {
        if (!undoStack.empty()) {
            text = undoStack.top();
            undoStack.pop();
        } else {
            cout << "Nothing to undo." << endl;
        }
    }

    void display() {
        cout << text << endl;
    }
};

int main() {
    TextEditor editor;

    while (true) {
        cout << "\n1. Insert Text\n2. Undo\n3. Display\n4. Exit\n";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string s;
                cout << "Enter text: ";
                getline(cin, s);
                editor.insert(s);
                break;
            }
            case 2:
                editor.undo();
                break;
            case 3:
                editor.display();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
