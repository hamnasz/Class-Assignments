#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string str) {
    stack<char> s;

    // Traverse each character in the string
    for (char c : str) {
        // If the character is an opening bracket, push it onto the stack
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
        // If the character is a closing bracket, check for balance
        else if (c == ')' || c == '}' || c == ']') {
            // If stack is empty, return false
            if (s.empty()) {
                return false;
            }

            // Check if the top of the stack matches the corresponding opening bracket
            char top = s.top();
            if ((c == ')' && top == '(') || 
                (c == '}' && top == '{') || 
                (c == ']' && top == '[')) {
                s.pop(); // If they match, pop the opening bracket
            } 
			else {
                return false; 
            }
        }
    }

    // If the stack is empty at the end, all brackets are balanced
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
