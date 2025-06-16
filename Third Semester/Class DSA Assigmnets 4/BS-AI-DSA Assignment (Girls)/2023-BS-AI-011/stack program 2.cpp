//Write a program to check if a given string of parentheses is balanced (e.g., “(())” is balanced, but “(()” is not).
#include <iostream>
#include <stack>

using namespace std;

bool isBalanced(const char* str) {
    stack<char> s;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '(') {
            s.push(str[i]);
        } else if (str[i] == ')') {
            if (s.empty()) {
                return false;
            }
            s.pop();
        }
        i++;
    }
    return s.empty();
}

int main() {
    char input[100];
    cout << "Enter a string of parentheses: ";
    cin >> input;

    if (isBalanced(input)) {
        cout << "The string is balanced.\n";
    } else {
        cout << "The string is not balanced.\n";
    }

    return 0;
}
