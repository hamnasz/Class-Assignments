#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Function to check if the parentheses are balanced
bool areParenthesesBalanced(const string& str) {
    stack<char> s;

    for (char ch : str) {
        // If the character is an opening bracket, push it onto the stack
        if (ch == '(') {
            s.push(ch);
        }
        // If the character is a closing bracket, check for balance
        else if (ch == ')') {
            // If the stack is empty, there's no matching opening bracket
            if (s.empty()) {
                return false;
            }
            // Pop the opening bracket from the stack
            s.pop();
        }
    }

    // If the stack is empty, all brackets were matched
    return s.empty();
}

int main() {
    string input;

    cout << "Enter a string of parentheses: ";
    cin >> input;

    if (areParenthesesBalanced(input)) {
        cout << "The parentheses are balanced." << endl;
    } else {
        cout << "The parentheses are not balanced." << endl;
    }

    return 0;
}

