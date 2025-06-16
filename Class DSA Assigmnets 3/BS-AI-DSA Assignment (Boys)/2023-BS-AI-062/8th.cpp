#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BrowserHistory {
private:
    stack<string> history;
    stack<string> future;

public:
    void visit(const string &url) {
        history.push(url);
        while (!future.empty()) {
            future.pop();  // Clear future stack when a new page is visited
        }
    }

    void goBack() {
        if (history.empty()) {
            cout << "No more history.\n";
            return;
        }
        future.push(history.top());
        history.pop();
    }

    void current() {
        if (history.empty()) {
            cout << "No current page.\n";
        } else {
            cout << "Current page: " << history.top() << "\n";
        }
    }

    void goForward() {
        if (future.empty()) {
            cout << "No forward history.\n";
            return;
        }
        history.push(future.top());
        future.pop();
    }
};

int main() {
    BrowserHistory browser;

    browser.visit("https://example.com");
    browser.current();
    browser.visit("https://example.com/page1");
    browser.current();
    browser.visit("https://example.com/page2");
    browser.current();
    browser.goBack();
    browser.current();
    browser.goBack();
    browser.current();
    browser.goForward();
    browser.current();

    return 0;
}
