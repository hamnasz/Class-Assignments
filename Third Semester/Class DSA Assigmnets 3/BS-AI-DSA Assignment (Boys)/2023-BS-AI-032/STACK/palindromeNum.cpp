#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;

    stack<char> charStack;
    
    for (char ch : word) {
        charStack.push(ch);
    }

    string reversedWord;
    while (!charStack.empty()) {
        reversedWord += charStack.top();
        charStack.pop();
    }

    if (word == reversedWord) {
        cout << word << " is a palindrome." << endl;
    } else {
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}
