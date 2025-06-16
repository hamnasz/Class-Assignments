// Copying First Array to Second Array in Reverse Order
#include<iostream>
using namespace std;
int main()
{
    int arr1[5], arr2[5];

    // Storing Values in Array 1 as Input From User
    cout<<"Enter 5 Values: ";
    for(int i=0; i<5; i++)
    {
        cin>>arr1[i];
    }
    // Displaying Values of Array 1
    cout<<"Array 1: " << endl;
    for(int i=0; i<5; i++)
    {
        cout<<arr1[i]<<endl;
    }

    // Copying Values of Array 1 into Array 2 in Reverse Order
    int n=0;
    for(int i=4; i>=0; i--)
    {
        arr2[i] = arr1[n];
        n++;
    }

    // Displaying Values of Array 2
    cout<<"Array 2: " << endl;
    for(int i=0; i<5; i++)
    {
        cout<<arr2[i]<<endl;
    }
    return 0;
}