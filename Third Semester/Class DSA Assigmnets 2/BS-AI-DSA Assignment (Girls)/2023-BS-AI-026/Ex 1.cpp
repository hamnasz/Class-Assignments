#include <iostream>
using namespace std;
int main() {
    int I[2][2] = {{1, 8}, {9, 4}};
    int N[2][2] = {{5, 6}, {7, 6}};
 int T[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            T[i][j] = I[i][j] + N[i][j];
        }
    }
  
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << T[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}