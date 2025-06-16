#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> history;
    string command;

    while (true) {
        cout << "\nCommands: visit <page>, back, current, exit" <<endl;
        cout << "Enter command: ";
        getline(cin, command);

        if (command.substr(0, 6) == "visit ") 
		{
            string page = command.substr(6);
            history.push(page);
            cout << "Visited: " << page <<endl;
        } 
		else if (command == "back") {
            if (history.empty()) {
                cout << "No history to go back to." <<endl;
            } else {
                string lastPage = history.top();
                history.pop();
                cout << "Went back from: " << lastPage <<endl;
                if (!history.empty()) {
                    cout << "Current page: " << history.top() <<endl;
                } else {
                    cout << "No current page." <<endl;
                }
            }
        } else if (command == "current") {
            if (history.empty()) {
                cout << "No pages visited." <<endl;
            } else {
                cout << "Current page: " << history.top() <<endl;
            }
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command. Please try again." <<endl;
        }
    }

    return 0;
}