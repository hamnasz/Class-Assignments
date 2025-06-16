#include <iostream>
#include <stack>
using namespace std;

bool isPalindrome(string s) {
    stack<char> stk;
    int n = s.length();

    // Push all characters of the string to the stack
    for (int i = 0; i < n; i++) {
        stk.push(s[i]);
    }

    // Compare the characters of the string with the characters popped from the stack
    for (int i = 0; i < n; i++) {
        if (s[i] != stk.top()) {
            return false;
        }
        stk.pop();
    }

    return true;
}

int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;

    if (isPalindrome(word)) {
        cout << word << " is a palindrome.\n";
    } else {
        cout << word << " is not a palindrome.\n";
    }

    return 0;
}
