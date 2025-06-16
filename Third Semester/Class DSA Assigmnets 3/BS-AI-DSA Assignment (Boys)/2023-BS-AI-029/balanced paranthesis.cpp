#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string& str) {
    stack<char> s;

    // Iterate through each character in the string
    for (char c : str) {
        // If the character is an opening bracket, push it onto the stack
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
        // If the character is a closing bracket
        else if (c == ')' || c == '}' || c == ']') {
            // Check if the stack is empty (unmatched closing bracket)
            if (s.empty()) {
                return false;
            }

            // Check if the top of the stack matches the closing bracket
            char top = s.top();
            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[')) {
                s.pop(); // Pop the matched opening bracket
            } else {
                return false; // Mismatched brackets
            }
        }
    }

    // If the stack is empty, all brackets were matched
    return s.empty();
}

int main() {
    // Get the string of parentheses from the user
    string input;
    cout << "Enter a string of parentheses: ";
    cin >> input;

    // Check if the string is balanced
    if (isBalanced(input)) {
        cout << "The string is balanced." << endl;
    } else {
        cout << "The string is not balanced." << endl;
    }

    return 0;
}
