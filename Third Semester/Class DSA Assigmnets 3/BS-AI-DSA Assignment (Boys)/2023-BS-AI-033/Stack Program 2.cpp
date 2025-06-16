#include <iostream>
#include <stack>
#include <string>

int main() {
    std::stack<char> s;
    std::string input;
    
    std::cout << "Enter a string of parentheses: ";
    std::cin >> input;

    bool balanced = true; // Assume the string is balanced initially

    for (char ch : input) {
        // Push opening brackets onto the stack
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        }
        // Check for matching closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') {
            // If stack is empty or top of stack doesn't match, it's unbalanced
            if (s.empty() || 
                (ch == ')' && s.top() != '(') ||
                (ch == '}' && s.top() != '{') ||
                (ch == ']' && s.top() != '[')) {
                balanced = false;
                break;
            }
            s.pop();
        }
    }

    // If the stack is not empty, it's unbalanced
    if (!s.empty()) {
        balanced = false;
    }

    if (balanced) {
        std::cout << "The string is balanced.\n";
    } else {
        std::cout << "The string is not balanced.\n";
    }

    return 0;
}
