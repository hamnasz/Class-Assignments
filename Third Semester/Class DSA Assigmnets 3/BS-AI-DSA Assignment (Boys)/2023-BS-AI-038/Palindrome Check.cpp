#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isPalindrome(const string &str) {
    stack<char> s;
    for (char ch : str) {
        s.push(ch);
    }
    
    for (char ch : str) {
        if (s.top() != ch) return false;
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