#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool isPalindrome(const string& word) {
    stack<char> charStack;
    for (char ch : word) {
        charStack.push(ch);
    }
    string reversedWord;
    while (!charStack.empty()) {
        reversedWord += charStack.top();
        charStack.pop();
    }
    return word == reversedWord;
}
int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;
    if (isPalindrome(word)) {
        cout << word << " is a palindrome." << endl;
    } else {
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}