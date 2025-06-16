#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int new_size = size + 1;
    int new_arr[new_size];
    int element = 3, pos = 2;


    for (int i = 0; i < pos; i++) {
        new_arr[i] = arr[i];
    }
    
  
    new_arr[pos] = element;

  
    for (int i = pos + 1; i < new_size; i++) {
        new_arr[i] = arr[i - 1];
    }


    cout << "Array after insertion: ";
    for (int i = 0; i < new_size; i++) {
        cout << new_arr[i] << " ";
    }
    cout << endl;

    return 0;
}

