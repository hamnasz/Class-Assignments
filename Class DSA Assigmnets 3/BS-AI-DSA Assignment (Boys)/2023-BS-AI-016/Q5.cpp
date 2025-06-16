#include <iostream>
using namespace std;

void removeDuplicates(int arr[]) {
    int unique[10]; 
    int count = -1; 

    for (int i = 0; i < 10; i++) {
        int flag = 0;

        for (int j = 0; j < count; j++)  {
            if (arr[i] == unique[j]) {
                flag++;
                break;
            }
        }

        if (flag == 0) {
            unique[++count] = arr[i];
        }
    }

    cout << "Unique elements: ";
    for (int i = 0; i <= count; i++) 
    {
        cout << unique[i] << " ";
    }
    cout << "\n";
}

int main() {
    int arr[10] = {4, 5, 2, 4, 5, 3, 2, 1, 3, 8};

    std::cout << "Original array: ";
    for (int i = 0; i < 10; ++i) 
    {
        cout << arr[i] << " ";
    }
    cout << "\n";

    removeDuplicates(arr, 10);

    return 0;
}
