#include<iostream>
using namespace std;

int main() {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{2, 0}, {1, 2}};
    int result[2][2] = {0};

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    //multiplication of matrices
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
