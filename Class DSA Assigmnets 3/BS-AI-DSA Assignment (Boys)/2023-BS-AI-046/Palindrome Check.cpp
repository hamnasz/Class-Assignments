#include <iostream>
#include <stack>
using namespace std;

int main() {
    string word, reversed_word;
    stack<char> s;

    cout << "Enter a word: ";
    cin >> word;

    for (char c : word) s.push(c);
    while (!s.empty()) {
        reversed_word += s.top();
        s.pop();
    }

    if (word == reversed_word) cout << "It's a palindrome." << endl;
    else cout << "Not a palindrome." << endl;
    return 0;
}
