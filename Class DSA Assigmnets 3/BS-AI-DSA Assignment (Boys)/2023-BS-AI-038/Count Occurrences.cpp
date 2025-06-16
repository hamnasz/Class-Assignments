#include <iostream>
using namespace std;

int main() {
    char arr[10];
    char ch;
    int count = 0;
    
    cout << "Enter 10 characters: ";
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
    }
    
    cout << "Enter character to count: ";
    cin >> ch;
    
    for (int i = 0; i < 10; i++) {
        if (arr[i] == ch) count++;
    }
    
    cout << "Character '" << ch << "' occurs " << count << " times." << endl;
    return 0;
}