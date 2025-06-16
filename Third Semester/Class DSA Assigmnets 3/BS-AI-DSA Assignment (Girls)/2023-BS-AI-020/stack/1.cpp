#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isPalindrome(const string& str) {
    stack<char> s;
    
    // Push all characters onto the stack
    for (char ch : str) {
        s.push(ch);
    }
    
    // Compare characters from the original string and the stack
    for (char ch : str) {
        if (ch != s.top()) {
            return false;
        }
        s.pop();
    }
    
    return true;
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
