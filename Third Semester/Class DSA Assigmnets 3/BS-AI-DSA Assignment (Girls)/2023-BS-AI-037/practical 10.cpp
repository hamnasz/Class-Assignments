#include <iostream>
#include <stack>
#include <string>

class TextEditor {
private:
    std::stack<std::string> history;  // Stack to keep track of text states
    std::string currentText;

public:
    void typeText(const std::string& text) {
        // Push the current state onto the stack before making changes
        history.push(currentText);
        // Append the new text to the current state
        currentText += text;
        std::cout << "Typed: " << text << std::endl;
    }

    void undo() {
        if (!history.empty()) {
            // Undo the last action by reverting to the previous state
            currentText = history.top();
            history.pop();
            std::cout << "Undo successful." << std::endl;
        } else {
            std::cout << "No actions to undo." << std::endl;
        }
    }

    void showText() const {
        // Display the current text
        std::cout << "Current text: " << currentText << std::endl;
    }
};

int main() {
    TextEditor editor;
    editor.typeText("Hello, ");
    editor.showText();

    editor.typeText("world!");
    editor.showText();

    editor.undo();
    editor.showText();

    editor.undo();
    editor.showText();

    editor.undo();  // Attempting to undo with an empty history stack

    return 0;
}
