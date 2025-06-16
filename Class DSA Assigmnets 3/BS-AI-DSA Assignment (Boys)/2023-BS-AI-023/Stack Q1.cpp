#include <iostream>
#include <stack>
using namespace std;

int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;
    stack<char> s;
    for(char c : word) s.push(c);
    string reversed;
    while(!s.empty()) {
        reversed += s.top();
        s.pop();
    }
    if(word == reversed) cout << word << " is a palindrome." << endl;
    else cout << word << " is not a palindrome." << endl;
    return 0;
}
