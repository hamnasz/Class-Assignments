#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<string> history;
    string currentPage;

    while (true) {
        cout << "\nCurrent Page: " << (currentPage.empty() ? "None" : currentPage) << endl;
        cout << "Enter command (visit <page>, back, exit): ";
        
        string command;
        getline(cin, command);

        if (command.rfind("visit ", 0) == 0) {
            if (!currentPage.empty()) {
                history.push(currentPage); 
            }
            currentPage = command.substr(6);
            cout << "Visiting: " << currentPage << endl;
        } else if (command == "back") {
            if (!history.empty()) {
                currentPage = history.top();
                history.pop();
                cout << "Going back to: " << currentPage << endl;
            } else {
                cout << "No more pages in history." << endl;
            }
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}
