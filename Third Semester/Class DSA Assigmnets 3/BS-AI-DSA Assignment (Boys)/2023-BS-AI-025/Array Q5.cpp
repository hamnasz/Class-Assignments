#include <iostream>
using namespace std;
int main() {
    int arr[10], NewArr[10], Count=0;
    cout << "Enter 10 integers: ";
    for(int i = 0; i < 10; i++) {
        cin >> arr[i];
        bool Duplicate = false;
        for(int j=0; j<Count; j++) {
            if(arr[i] == NewArr[j]) {
                Duplicate=true;
                break;
            }
        }
        if(Duplicate) {
            NewArr[Count] = arr[i];
            Count++;
        }
    }
    cout << "Array without duplicates: ";
    for(int i = 0;i<Count; i++) {
        cout << NewArr[i] << " ";
    }
    cout<<endl;
    return 0;
}
