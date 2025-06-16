#include <iostream>
#include <stack>
using namespace std;

bool isPalindrome(string str) {
    stack<char> s;
    for (char c : str) {
        s.push(c);  // Push each character onto the stack
    }
    
    for (char c : str) {
        if (c != s.top()) {  // Compare each character with the stack's top element
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
        cout << word << " is a palindrome!" << endl;
    } else {
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}
