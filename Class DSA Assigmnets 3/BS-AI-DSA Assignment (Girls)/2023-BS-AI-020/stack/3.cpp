#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<string> history;
    string currentPage;
    string choice;

    while (true) {
        cout << "Enter a new page to visit (or 'back' to go back): ";
        cin >> choice;

        if (choice == "back") {
            if (history.empty()) {
                cout << "No pages in history to go back to." << endl;
            } else {
                currentPage = history.top();
                history.pop();
                cout << "Going back to: " << currentPage << endl;
            }
        } else {
            if (!currentPage.empty()) {
                history.push(currentPage); // Push current page to history
            }
            currentPage = choice; // Update current page
            cout << "Visited: " << currentPage << endl;
        }
    }

    return 0;
}
