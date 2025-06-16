#include <iostream>
using namespace std;

int main() {
    char arr[10];
    char check;
    cout<<"Enter 10 characters: ";
    for(int i = 0; i < 10; i++) {
        cin >> arr[i];
    }
    cout<<"Enter character to count: ";
    cin>>check;
    int count = 0;
    for(int i = 0; i < 10; i++) {
        if(arr[i] == check) count++;
    }
    cout << "Occurrences of " << check << ": " << count << endl;
    return 0;
}
