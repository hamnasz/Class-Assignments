#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

bool areParenthesesBalanced(const string& str) {
    stack<char> parenthesesStack;
    unordered_map<char, char> parenthesesMap = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    for (char c : str) {
        if (c == '(' || c == '[' || c == '{') {
            parenthesesStack.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (parenthesesStack.empty() || parenthesesStack.top() != parenthesesMap[c]) {
                return false;
            }
            parenthesesStack.pop();
        }
    }
    return parenthesesStack.empty();
}

int main() {
    string str;
    cout << "Enter a string of parentheses: ";
    cin >> str;

    if (areParenthesesBalanced(str)) {
        cout << str << " is balanced." << endl;
    } else {
        cout << str << " is not balanced." <<endl;
    }
    return 0;
}
