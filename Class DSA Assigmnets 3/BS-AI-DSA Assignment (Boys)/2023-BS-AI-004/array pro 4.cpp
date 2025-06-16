#include <iostream>
using namespace std;

int main() {
    char arr[] = {'a', 'b', 'a', 'c', 'a', 'd', 'b', 'a'};
    char ch;
    cout << "Enter character to count: ";
    cin >> ch;
    int count = 0;
    for (char i : arr) {
        if (i == ch) count++;
    }
    cout << "Occurrences of " << ch << ": " << count << endl;
    return 0;
}
