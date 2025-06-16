#include <iostream>
#include <stack>
#include <string>

class BrowserHistory {
private:
    std::stack<std::string> history;  

public:
    void visit(const std::string& url) {
       
        history.push(url);
        std::cout << "Visited: " << url << std::endl;
    }

    void goBack() {
       
        if (!history.empty()) {
            std::cout << "Going back from: " << history.top() << std::endl;
            history.pop();
        } else {
            std::cout << "No previous page to go back to." << std::endl;
        }
    }

    void currentPage() const {
        
        if (!history.empty()) {
            std::cout << "Current page: " << history.top() << std::endl;
        } else {
            std::cout << "No pages in history." << std::endl;
        }
    }
};

int main() {
    BrowserHistory browser;
    browser.visit("google.com");
    browser.visit("facebook.com");
    browser.visit("youtube.com");
    browser.currentPage();
    browser.goBack();
    browser.currentPage();
    browser.goBack();
    browser.currentPage();
    browser.goBack();

    return 0;
}
