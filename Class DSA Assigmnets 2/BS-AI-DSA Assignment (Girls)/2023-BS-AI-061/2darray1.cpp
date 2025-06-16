#include <iostream>
using namespace std;
int main() {
    int marks[3][2] = {
        {85, 90},  
        {78, 82},  
        {92, 88}   
    };
    for (int i = 0; i < 3; i++) {
        cout << "Student " << i+1 << " Marks: ";
        for (int j = 0; j < 2; j++) {
            cout << marks[i][j] << " ";  
        }
        cout << endl;
    }
    return 0;
}
