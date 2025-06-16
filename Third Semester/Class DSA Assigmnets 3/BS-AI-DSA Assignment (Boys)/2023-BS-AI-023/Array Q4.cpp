#include <iostream>
using namespace std;

int main() {
    char arr[10];
    char target;
    cout << "Enter 10 characters: ";
    for(int i = 0; i < 10; i++) {
        cin >> arr[i];
    }
    cout << "Enter character to count: ";
    cin >> target;
    int count = 0;
    for(int i = 0; i < 10; i++) {
        if(arr[i] == target) count++;
    }
    cout << "Occurrences of " << target << ": " << count << endl;
    return 0;
}
