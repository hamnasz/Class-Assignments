#include <iostream>
using namespace std;
int main() {
    int balance[3][2] = {
        {1, 90},  
        {2, 82},  
        {3, 88}   
    };
    for (int i = 0; i < 3; i++) {
        cout << "balance " << i+1 << " accounts: ";
        for (int j = 0; j < 2; j++) {
            cout << balance[i][j] << " ";  
        }
        cout << endl;
    }
    return 0;
}
