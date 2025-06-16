#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BrowserHistory {
private:
    stack<string> backwardStack;
    stack<string> forwardStack;

public:
    void visit(const string& url) {
        forwardStack = stack<string>(); // Clear forward stack
        backwardStack.push(url);
        cout << "Visited: " << url << endl;
    }

    void goBack() {
        if (backwardStack.size() < 2) {
            cout << "Cannot go back. No previous pages." << endl;
            return;
        }

        string currentUrl = backwardStack.top();
        backwardStack.pop();
        forwardStack.push(currentUrl);

        cout << "Went back to: " << backwardStack.top() << endl;
    }

    void goForward() {
        if (forwardStack.empty()) {
            cout << "Cannot go forward. No next pages." << endl;
            return;
        }

        string nextUrl = forwardStack.top();
        forwardStack.pop();
        backwardStack.push(nextUrl);

        cout << "Went forward to: " << nextUrl << endl;
    }

    void printHistory() {
        cout << "Browser History:" << endl;
        stack<string> temp = backwardStack;

        while (!temp.empty()) {
            cout << temp.top() << endl;
            temp.pop();
        }
    }
};

int main() {
    BrowserHistory browser;

    while (true) {
        cout << "\nBrowser Menu:" << endl;
        cout << "1. Visit URL" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. Print History" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string url;
                cout << "Enter URL: ";
                cin >> url;
                browser.visit(url);
                break;
            }
            case 2:
                browser.goBack();
                break;
            case 3:
                browser.goForward();
                break;
            case 4:
                browser.printHistory();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
