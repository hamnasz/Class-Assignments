#include <iostream>
using namespace std;
int main() {
    int arr1[3] = {1, 2, 3};
    int arr2[2] = {4, 5};
    int merged[5];

    for (int i = 0; i < 3; i++) {
        merged[i] = arr1[i];
    }
    for (int i = 0; i < 2; i++) {
        merged[3 + i] = arr2[i];
    }

    for (int i = 0; i < 5; i++) {
        cout << merged[i] << " ";
    }
    return 0;
}
