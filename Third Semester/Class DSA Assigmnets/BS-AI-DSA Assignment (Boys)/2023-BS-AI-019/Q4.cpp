// Searching a Number from Array
#include <iostream>
using namespace std;

int main()
{
    int n, count, num[10];

    // Take Numbers as Input from User using Loop
    cout<<"Enter any 10 Numbers:"<<endl;
    for(int i=0; i<10; i++)
    {
        cin>>num[i];
    }

    // Take Number to Search as Input from User
    cout<<"Enter Number to Find: ";
    cin>>n;

    // Search and Display Index of Number using Loop
    for(int i=0; i<10; i++)
    {
        if(n == num[i])
        {
            cout<<"Found at Index: "<<i<<endl;
            count++;
        }
    }
    cout<<"Total Occurencies: "<<count;
    return 0;
}