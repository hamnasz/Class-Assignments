#include <iostream>
#include <stack>
using namespace std;

bool isPalindrome(const string &word) {
    stack<char> s;
    for (char c : word) s.push(c);
    for (char c : word) {
        if (c != s.top()) return false;
        s.pop();
    }
    return true;
}

int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;
    cout << (isPalindrome(word) ? "Palindrome" : "Not Palindrome") << endl;
    return 0;
}
