#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isBalanced(const string &s) {
    stack<char> stack;

    for (char ch : s) {
        
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        } 
        // Check closing brackets
        else if (ch == ')' || ch == '}' || ch == ']') {
            
            if (stack.empty()) return false;

            char top = stack.top();
            if ((ch == ')' && top == '(') ||
                (ch == '}' && top == '{') ||
                (ch == ']' && top == '[')) {
                stack.pop();  
				
            } else {
                return false; 
            }
        }
    }

    
    return stack.empty();
}

int main() {
    string s;
    cout << "Enter a string of parentheses: ";
    cin >> s;

    if (isBalanced(s)) {
        cout << "The string is balanced.\n";
    } else {
        cout << "The string is not balanced.\n";
    }

    return 0;
}
