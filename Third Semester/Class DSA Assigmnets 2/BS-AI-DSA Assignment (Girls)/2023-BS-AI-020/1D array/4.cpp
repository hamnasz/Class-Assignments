#include<iostream>
using namespace std;

int main() {
    int arr[5] = {12, 9, 7, 25, 18};
    int max = arr[0];
    for(int i = 1; i < 5; i++) {
        if(arr[i] > max)
            max = arr[i];
    }
    cout << "Maximum element: " << max;
    return 0;
}
