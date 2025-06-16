#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isPalindrome(string word) {
    stack<char> st;
    int n = word.length();

    // Push all characters of the word onto the stack
    for (int i = 0; i < n; i++) {
        st.push(word[i]);
    }

    // Pop characters from the stack and compare with the original word
    for (int i = 0; i < n; i++) {
        if (word[i] != st.top()) {
            return false;
        }
        st.pop();
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
