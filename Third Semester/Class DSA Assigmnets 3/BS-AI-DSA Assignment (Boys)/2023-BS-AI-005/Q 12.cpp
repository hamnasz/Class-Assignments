#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool isBalanced(const string& str) {
    stack<char> s;
    for (char ch : str) {
        if (ch == '(' || ch == '[' || ch == '{' || ch == '<') {
            s.push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}' || ch == '>') {
            if (s.empty()) {
                return false;
            }
            char top = s.top();
            s.pop();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{') ||
                (ch == '>' && top != '<')) {
                return false; 
            }
        }
    }

    return s.empty(); 
}
int main() {
    string input;
    cout << "Enter a string of parentheses: ";
    cin >> input;

    if (isBalanced(input)) {
        cout << "The string is balanced." << endl;
    } else {
        cout << "The string is not balanced." << endl;
    }
    return 0;
}