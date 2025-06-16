#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(string str) {
    stack<char> s;
    for (char ch : str) {
        if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            if (s.empty()) {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

int main() {
    string str = "(())";
    if (isBalanced(str)) {
        cout << "The string is balanced." << endl;
    } else {
        cout << "The string is not balanced." << endl;
    }
    
    str = "(()";
    if (isBalanced(str)) {
        cout << "The string is balanced." << endl;
    } else {
        cout << "The string is not balanced." << endl;
    }
    
    return 0;
}
