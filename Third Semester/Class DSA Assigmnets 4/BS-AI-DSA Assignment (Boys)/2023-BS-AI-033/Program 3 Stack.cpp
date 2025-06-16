#include <iostream>
#include <stack>
#include <string>

bool isBalanced(const std::string& str) {
    std::stack<char> s;

    for (char ch : str) {
        if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            if (s.empty() || s.top() != '(') {
                return false;
            }
            s.pop();
        }
    }

    return s.empty();
}

int main() {
    std::string str = "(())"; // Test string
    if (isBalanced(str)) {
        std::cout << "The string is balanced." << std::endl;
    } else {
        std::cout << "The string is not balanced." << std::endl;
    }

    str = "(()"; // Test another string
    if (isBalanced(str)) {
        std::cout << "The string is balanced." << std::endl;
    } else {
        std::cout << "The string is not balanced." << std::endl;
    }

    return 0;
}
