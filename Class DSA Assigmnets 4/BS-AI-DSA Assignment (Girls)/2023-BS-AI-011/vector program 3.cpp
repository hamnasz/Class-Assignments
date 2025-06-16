//Create a program to sort a vector of integers in ascending order.
#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    vector<int> myVector = {5, 2, 8, 1, 9};

    cout << "Unsorted Vector: ";
    for (int num : myVector) {
        cout << num << " ";
    }
    cout << endl;

    bubbleSort(myVector);

    cout << "Sorted Vector: ";
    for (int num : myVector) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}