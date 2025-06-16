#include <iostream>
#include <stack>
using namespace std;

bool areParenthesesBalanced(string expression) {
    stack<char> charStack;
    
    for(char character : expression) {
        if(character == '(' || character == '{' || character == '[') 
            charStack.push(character);
        else {
            if(charStack.empty()) return false;
            char topCharacter = charStack.top();
            charStack.pop();
            if((character == ')' && topCharacter != '(') || 
               (character == '}' && topCharacter != '{') || 
               (character == ']' && topCharacter != '[')) 
                return false;
        }
    }
    return charStack.empty();
}

int main() {
    string expression;
    cout << "Enter an expression containing parentheses: ";
    cin >> expression;
    
    if(areParenthesesBalanced(expression)) 
        cout << "The parentheses are correctly balanced." << endl;
    else 
        cout << "The parentheses are not balanced." << endl;
    
    return 0;
}
