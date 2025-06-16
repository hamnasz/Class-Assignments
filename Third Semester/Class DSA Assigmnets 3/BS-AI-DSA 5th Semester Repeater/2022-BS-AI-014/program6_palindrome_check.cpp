#include <iostream>
#include <stack>
#include <string>
using namespace std;

void palindromeCheck() {
    string word;

    cout << "Enter a word to check if it's a palindrome: ";
    cin >> word;

    stack<char> s;
    for (char ch : word) {
        s.push(ch);
    }

    string reversed_word = "";
    while (!s.empty()) {
        reversed_word += s.top();
        s.pop();
    }

    cout << "Is Palindrome: " << (word == reversed_word ? "Yes" : "No") << "\n";
}

int main() {
    palindromeCheck();
    return 0;
}
