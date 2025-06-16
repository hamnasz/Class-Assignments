//  Initialize an array of integers and print all the elements

#include <iostream>
using namespace std;
int main()
{
    int size = 10;
    int arr[size];

    // Initialize array by taking input from user
    cout<<"Enter 10 Numbers: "<<endl;
    for(int i=0; i<size; i++)
    {
        cin>>arr[i];
    }

    // Print array
    cout<<"\nPrint: ";
    for(int i=0; i<size; i++)
    {
        cout<<arr[i]<<", ";
    }

    return 0;
}