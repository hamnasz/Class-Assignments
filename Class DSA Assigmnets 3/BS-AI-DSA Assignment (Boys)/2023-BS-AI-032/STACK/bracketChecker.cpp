#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string& expression) {
    stack<char> s;
    
    for (char ch : expression) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.empty()) {
                return false;
            }
            char top = s.top();
            s.pop();
            if ((ch == ')' && top != '(') || 
                (ch == '}' && top != '{') || 
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }
    
    return s.empty();
}

int main() {
    string expression;
    cout << "Enter a string of parentheses: ";
    cin >> expression;

    if (isBalanced(expression)) {
        cout << "The string is balanced." << endl;
    } else {
        cout << "The string is not balanced." << endl;
    }

    return 0;
}
