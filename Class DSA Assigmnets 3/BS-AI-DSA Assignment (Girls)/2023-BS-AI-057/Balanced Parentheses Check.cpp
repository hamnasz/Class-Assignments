#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(string str) {
    stack<char> s;
    for (char c : str) {
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        } else if (c == ')' && !s.empty() && s.top() == '(') {
            s.pop();
        } else if (c == '}' && !s.empty() && s.top() == '{') {
            s.pop();
        } else if (c == ']' && !s.empty() && s.top() == '[') {
            s.pop();
        } else {
            return false;
        }
    }
    return s.empty();
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    cin >> expression;
    
    if (isBalanced(expression)) {
        cout << "The parentheses are balanced." << endl;
    } else {
        cout << "The parentheses are not balanced." << endl;
    }

    return 0;
}
