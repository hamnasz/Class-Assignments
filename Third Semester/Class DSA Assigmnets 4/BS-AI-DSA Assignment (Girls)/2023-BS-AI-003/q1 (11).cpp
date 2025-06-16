#include <iostream>
#include <stack>
using namespace std;

bool isBalanced(const string& str) {
    stack<char> s;
    
    for (char ch : str) {
        if (ch == '(') {
            s.push(ch); // Push opening bracket onto the stack
        } else if (ch == ')') {
            if (s.empty()) {
                return false; // Unmatched closing bracket
            }
            s.pop(); // Pop the matched opening bracket
        }
    }
    
    return s.empty(); // Check if all opening brackets were matched
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
