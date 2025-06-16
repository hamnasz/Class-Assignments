#include <iostream>
#include <stack>
#include <string>

class TextEditor {
public:
    void addAction(const std::string& action) {
        actions.push(action);
        std::cout << "Action added: " << action << std::endl;
    }

    void undo() {
        if (!actions.empty()) {
            std::string lastAction = actions.top();
            actions.pop();
            std::cout << "Undid action: " << lastAction << std::endl;
        } else {
            std::cout << "No actions to undo." << std::endl;
        }
    }

private:
    std::stack<std::string> actions;
};

int main() {
    TextEditor editor;
    std::string input;
    int choice;

    while (true) {
        std::cout << "Choose an action:\n1. Add Action\n2. Undo\n3. Exit\n";
        std::cin >> choice;
        std::cin.ignore();  

        switch (choice) {
            case 1:
                std::cout << "Enter action: ";
                std::getline(std::cin, input);
                editor.addAction(input);
                break;
            case 2:
                editor.undo();
                break;
            case 3:
                std::cout << "Exiting the text editor." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
