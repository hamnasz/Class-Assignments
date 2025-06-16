#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> history;
    string currentPage;
    string command;
    
    while (true) {
        cout << "Enter a command (visit <url>, back, exit): ";
        getline(cin, command);

        if (command.find("visit ") == 0) {
            string url = command.substr(6); // Get the URL after "visit "
            if (!currentPage.empty()) {
                history.push(currentPage); // Save the current page before visiting a new one
            }
            currentPage = url;
            cout << "Visiting: " << currentPage << endl;
        } else if (command == "back") {
            if (!history.empty()) {
                currentPage = history.top(); // Go back to the previous page
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
