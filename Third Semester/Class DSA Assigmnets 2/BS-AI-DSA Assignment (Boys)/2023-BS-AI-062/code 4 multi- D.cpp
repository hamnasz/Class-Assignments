#include <iostream>
using namespace std;
int main() {
    int arr[3][3];
    cout << "Enter 9 elements for a 3x3 matrix:" <<endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
           cin >> arr[i][j];
        }
    }
    cout << "You entered:" <<endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j] << " ";
        }
        cout <<endl;
    }
    return 0;
}
