#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    string word, revWord;
    cout << "Enter a word: ";
    cin >> word;

    revWord = word;
    reverse(revWord.begin(), revWord.end());

    if (word == revWord) {
        cout << word << " is a palindrome." << endl;
    } else {
        cout << word << " is not a palindrome." << endl;
    }

    return 0;
}
