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
    std::string str1 = "(())";
    std::string str2 = "(()";

    std::cout << "The string \"" << str1 << "\" is " << (isBalanced(str1) ? "balanced." : "not balanced.") << std::endl;
    std::cout << "The string \"" << str2 << "\" is " << (isBalanced(str2) ? "balanced." : "not balanced.") << std::endl;

    return 0;
}
