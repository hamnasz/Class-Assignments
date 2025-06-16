#include <iostream>
using namespace std;
int main() {
    string sports[4]; 
    cout << "Enter the names of your sports: " << endl;
    for (int i = 0; i < 4; i++) {
        cin >> sports[i];
    }
    cout << "Your favorite sports are: ";
    for (int i = 0; i < 4; i++) {
        cout << sports[i] << " ";
    }
    cout << endl;
    return 0;
}
