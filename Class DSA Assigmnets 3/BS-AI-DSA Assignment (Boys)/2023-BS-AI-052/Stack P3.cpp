#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BrowserHistory {
private:
    stack<string> forwardStack;
    stack<string> backStack;

public:
    void visit(const string& page) {
        backStack.push(page);
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
    }

    string goBack() {
        if (backStack.empty()) {
            return "No previous pages.";
        }
        forwardStack.push(backStack.top());
        backStack.pop();
        return forwardStack.top();
    }

    string goForward() {
        if (forwardStack.empty()) {
            return "No next pages.";
        }
        backStack.push(forwardStack.top());
        forwardStack.pop();
        return backStack.top();
    }
};

int main() {
    BrowserHistory browser;
    string choice;

    while (true) {
        cout << "1. Visit\n2. Go Back\n3. Go Forward\n4. Exit\n";
        cin >> choice;

        if (choice == "1") {
            string page;
            cout << "Enter page URL: ";
            cin >> page;
            browser.visit(page);
        } else if (choice == "2") {
            cout << browser.goBack() << endl;
        } else if (choice == "3") {
            cout << browser.goForward() << endl;
        } else if (choice == "4") {
            break;
        }
    }
    return 0;
}
