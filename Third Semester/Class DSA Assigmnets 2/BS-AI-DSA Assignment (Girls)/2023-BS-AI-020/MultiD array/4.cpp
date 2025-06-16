#include<iostream>
using namespace std;

int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int trans[3][2];
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            trans[j][i] = arr[i][j];
        }
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 2; j++) {
            cout << trans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
