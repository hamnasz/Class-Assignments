#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string& str) {
    stack<char> s;
    
    for (char ch : str) {
        // Push opening brackets onto the stack
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else {
            // Check for closing brackets
            if (s.empty()) return false;
            char top = s.top();
            s.pop();
            if ((ch == ')' && top != '(') || 
                (ch == '}' && top != '{') || 
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return s.empty(); // Return true if stack is empty (balanced)
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    cin >> expression;

    if (isBalanced(expression)) {
        cout << "The expression is balanced." << endl;
    } else {
        cout << "The expression is not balanced." << endl;
    }

    return 0;
}
