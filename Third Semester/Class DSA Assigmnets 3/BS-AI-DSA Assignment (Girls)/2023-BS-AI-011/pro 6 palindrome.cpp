//1. Palindrome Check
#include <iostream>
#include <stack>
using namespace std;
bool Palindrome(const char* word) {
    stack<char> s;
    // Push characters onto the stack
    for (int i = 0; word[i] != '\0'; ++i) {
        s.push(word[i]);
    }
    // Compare characters from the original word with popped characters
    for (int i = 0; word[i] != '\0'; ++i) {
        if (word[i] != s.top()) {
            return false; // Not a palindrome
        }
        s.pop();
    }
    return true; // Palindrome
}

int main() {
    char word[100];
    cout << "Enter a word: ";
    cin >> word;

    if (Palindrome(word)) {
        cout << word << " is a palindrome." << endl;
    } else {
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}