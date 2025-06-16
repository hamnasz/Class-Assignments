#include <iostream>
#include <stack>
using namespace std;

// Function to check if the given string of parentheses is balanced
bool isBalanced(string str) {
    stack<char> s;  // Stack to keep track of opening parentheses

    // Iterate through each character in the string
    for (char ch : str) {
        if (ch == '(') {  // If the character is an opening parenthesis, push it onto the stack
            s.push(ch);
        } else if (ch == ')') {  // If the character is a closing parenthesis
            if (s.empty()) {  // If the stack is empty, the parentheses are unbalanced
                return false;
            }
            s.pop();  // Pop the matching opening parenthesis from the stack
        }
    }

    // If the stack is empty, the parentheses are balanced
    return s.empty();
}

int main() {
    string input;

    // Get the input string from the user
    cout << "Enter a string of parentheses: ";
    cin >> input;

    // Check if the parentheses are balanced
    if (isBalanced(input)) {
        cout << "The parentheses are balanced." << endl;
    } else {
        cout << "The parentheses are not balanced." << endl;
    }

    return 0;
}
