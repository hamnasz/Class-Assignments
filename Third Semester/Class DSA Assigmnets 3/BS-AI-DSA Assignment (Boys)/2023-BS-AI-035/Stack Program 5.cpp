#include <iostream>
#include <stack>
#include <string>

class SimpleTextEditor {
public:
    void recordAction(const std::string& action) {
        actionHistory.push(action);
        std::cout << "Recorded action: " << action << std::endl;
    }

    void undoLastAction() {
        if (!actionHistory.empty()) {
            std::string lastAction = actionHistory.top();
            actionHistory.pop();
            std::cout << "Reverted action: " << lastAction << std::endl;
        } else {
            std::cout << "No actions available to undo." << std::endl;
        }
    }

private:
    std::stack<std::string> actionHistory;
};

int main() {
    SimpleTextEditor editor;
    std::string userInput;
    int userChoice;

    while (true) {
        std::cout << "Select an action:\n1. Record Action\n2. Undo\n3. Exit\n";
        std::cin >> userChoice;
        std::cin.ignore();  

        switch (userChoice) {
            case 1:
                std::cout << "Please enter the action: ";
                std::getline(std::cin, userInput);
                editor.recordAction(userInput);
                break;
            case 2:
                editor.undoLastAction();
                break;
            case 3:
                std::cout << "Closing the text editor." << std::endl;
                return 0;
            default:
                std::cout << "Invalid selection. Please choose again." << std::endl;
        }
    }

    return 0;
}
