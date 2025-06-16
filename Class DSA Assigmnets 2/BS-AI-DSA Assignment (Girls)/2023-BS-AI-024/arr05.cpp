#include <iostream>
using namespace std;
int main() {
    int employee[3][2] = {
        {100, 90},  
        {289, 82},  
        {356, 88}   
    };
    for (int i = 0; i < 3; i++) {
        cout << "employee " << i+1 << " salary: ";
        for (int j = 0; j < 2; j++) {
            cout << employee[i][j] << " ";  
        }
        cout << endl;
    }
    return 0;
}