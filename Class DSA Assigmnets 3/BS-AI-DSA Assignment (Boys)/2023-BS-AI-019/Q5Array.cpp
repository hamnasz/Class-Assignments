#include <iostream>
using namespace std;

void removeDuplicates(int arr[], int size) 
{
    int unique[size]; // Temporary array to store unique elements
    int count = -1; // Counter for unique elements

    for (int i = 0; i < size; i++) 
    {
        int flag = 0;

        // Check if arr[i] is a duplicate by comparing it with elements in unique array
        for (int j = 0; j < count; j++) 
        {
            if (arr[i] == unique[j]) 
            {
                flag++;
                break;
            }
        }

        // If it's not a duplicate, add it to the unique array
        if (flag == 0) 
        {
            unique[++count] = arr[i];
        }
    }

    // Display unique elements
    cout << "Unique elements: ";
    for (int i = 0; i <= count; i++) 
    {
        cout << unique[i] << " ";
    }
    cout << "\n";
}

int main() 
{
    int size = 10;
    int arr[size] = {4, 5, 2, 4, 5, 3, 2, 1, 3, 8};

    std::cout << "Original array: ";
    for (int i = 0; i < size; ++i) 
    {
        cout << arr[i] << " ";
    }
    cout << "\n";

    removeDuplicates(arr, size);

    return 0;
}
