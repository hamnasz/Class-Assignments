#include <iostream>
#include <stack>
#include <string>
using namespace std;

int palindrome(string word) {
    stack<char> Stack;

    for (char c : word) {
        Stack.push(c);
    }

    for (char c : word) {
        if (c != Stack.top()) {
            cout<<"Not a Palindrome!";
            return 2;
        }
        Stack.pop();
    }
    cout<<" Palindrome!";
    return 1;
}
int main() {
    string word;
    cout << "Enter word: ";
    cin >> word;

    palindrome(word);
    return 0;
}
