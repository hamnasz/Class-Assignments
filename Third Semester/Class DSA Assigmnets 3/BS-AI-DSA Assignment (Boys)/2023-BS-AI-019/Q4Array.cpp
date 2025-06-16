// Searching a Number from Array
#include <iostream>
using namespace std;

void countOccurences(int size, char arr[], int count, int c)
{
    for(int i=0; i<size; i++)
    {
        if(c == arr[i])
        {
            cout<<"Found at Index: "<<i<<endl;
            count++;
        }
    }
    cout<<"Total Occurencies: "<<count;
}
int main()
{
    int size = 10;
    char arr[size], c;
    int count =0;

    // Take Numbers as Input from User using Loop
    cout<<"Enter any 10 Cahracters:"<<endl;
    for(int i=0; i<size; i++)
    {
        cin>>arr[i];
    }

    // Take Number to Search as Input from User
    cout<<"Enter Number to Find: ";
    cin>>c;

    // Search and Display Index of Number using Loop
    countOccurences(size, arr, count, c);
    return 0;
}