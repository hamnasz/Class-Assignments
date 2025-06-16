#include <iostream>
#include <stack>

using namespace std;

bool isBalanced(const string& str) {
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
    string input;
    cout << "Enter a string of parentheses: ";
    cin >> input;

    if (isBalanced(input)) {
        cout << "The string is balanced.\n";
    } else {
        cout << "The string is not balanced.\n";
    }

    return 0;
}
