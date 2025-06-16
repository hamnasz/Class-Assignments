//2. Balanced Parentheses
#include <iostream>
#include <stack>
using namespace std;
bool Balanced(const char* str) {
    stack<char> s;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            s.push(str[i]);
        } else {
            if (s.empty()) {
                return false; // Unbalanced
            }
            char top = s.top();
            s.pop();
            if ((str[i] == ')' && top != '(') || (str[i] == '}' && top != '{') || (str[i] == ']' && top != '[')) {
                return false; // Unbalanced
            }
        }
    }

    return s.empty(); // Balanced
}

int main() {
    char str[100];
    cout << "Enter a string of parentheses: ";
    cin >> str;

    if (Balanced(str)) {
        cout << "The string is balanced." << endl;
    } else {
        cout << "The string is not balanced." << endl;
    }

    return 0;
}