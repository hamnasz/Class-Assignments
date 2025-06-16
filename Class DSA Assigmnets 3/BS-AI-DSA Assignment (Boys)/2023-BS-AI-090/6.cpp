#include <iostream>
#include <stack>
using namespace std;

bool isPalindrome(string str) {
    stack<char> s;
    string reversedStr = "";

    for (char ch : str) {
        s.push(ch);
    }

    while (!s.empty()) {
        reversedStr += s.top();
        s.pop();
    }

    return str == reversedStr;
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
