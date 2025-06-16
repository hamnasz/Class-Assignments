#include <iostream>
#include <stack>
#include <string>
using namespace std;
class TextEditor {
private:
    stack<string> actions;
    string currentText;

public:
    void inputText(const string& text) {
        actions.push(currentText);
        currentText += text;
    }

    void undo() {
        if (!actions.empty()) {
            currentText = actions.top();
            actions.pop();
        } else {
            cout << "Nothing to undo.\n";
        }
    }

    void displayText() const {
        cout << "Current Text: " << currentText << "\n";
    }
};
int main() {
    TextEditor editor;
    editor.inputText("Hello, ");
    editor.displayText(); 
    editor.inputText("world!");
    editor.displayText(); 
    editor.undo();
    editor.displayText(); 
    editor.undo();
    editor.displayText();  
    editor.undo(); 
    return 0;
}