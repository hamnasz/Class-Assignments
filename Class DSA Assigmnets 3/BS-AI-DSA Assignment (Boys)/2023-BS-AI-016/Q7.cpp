#include <iostream>
#include <stack>
#include <string>
using namespace std;

int balanced(string value) {
    stack<char> Stack;

    for (char ch : value) {
        if (ch == '(' || ch == '{' || ch == '[') {
            Stack.push(ch);
        }

        else if (ch == ')' || ch == '}' || ch == ']') {
            if (Stack.empty()){
                cout<<"It is not Balanced!";
                return 3;
            }

            char t = Stack.t();
            Stack.pop();

            if ((ch == ')' && t != '(') || (ch == '}' && t != '{') || (ch == ']' && t != '[')) {
                cout<<"Not Balanced!";
                return 2;
            }
        }
    }

    cout<<"Balanced!";
    return 1;
}
int main() {
    string value;
    cout << "Enter a string of parentheses: ";
    cin >> value;
    balanced(value);
    return 0;
}
