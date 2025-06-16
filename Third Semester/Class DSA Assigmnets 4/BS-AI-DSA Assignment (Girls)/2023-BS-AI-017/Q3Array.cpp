// Reverses the elements of an array
#include <iostream>
using namespace std;
int main()
{
    // Initialize Array
    int size = 8;
    int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    // Display Numbers in Stored Order
    cout<<"\nPrint in Stored Order: ";
    for(int i=0; i<size; i++)
    {
        cout<<arr[i]<<", ";
    }

    // Display Numbers in Reverse Order
    cout<<"\nPrint in Reverse Order: ";
    for(int i=size-1; i>=0; i--)
    {
        cout<<arr[i]<<", ";
    }
    return 0;
}