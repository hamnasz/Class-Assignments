#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<std::string> actions;
    string command;

    while (true) {
        cout << "\nCommands: add <action>, undo, display, exit" <<endl;
        cout << "Enter command: ";
        getline(std::cin, command);

        if (command.substr(0, 4) == "add ") 
		{
            string action = command.substr(4);
            actions.push(action);
            cout << "Action added: " << action <<endl;
        } else if (command == "undo") 
		{
            if (actions.empty()) {
                cout << "No actions to undo." <<endl;
            } else {
                string lastAction = actions.top();
                actions.pop();
                cout << "Undid action: " << lastAction <<endl;
            }
        } else if (command == "display") 
		{
            if (actions.empty()) {
                cout << "No actions available." <<endl;
            } else {
                stack<string> temp = actions; 
                cout << "Current actions (most recent first):" <<endl;
                while (!temp.empty()) {
                    cout << temp.top() <<endl;
                    temp.pop();
                }
            }
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command. Please try again." <<endl;
        }
    }
    return 0;
}