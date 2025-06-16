// Reverse Numbers
#include <iostream>
using namespace std;
int main()
{
    int n;

    // Take Ammount of Numbers as Input from User
    cout<<"Enter Ammount of Numbers: ";
    cin>>n;
    int num[n];

    // Take Numbers as Input from User using Loop
    cout<<"Enter Numbers to Store: "<<endl;
    for(int i=0; i<n; i++)
    {
        cin>>num[i];
    }

    // Display Numbers in Stored Order as Output using Loop
    cout<<"\nDisplay in Stored Order: ";
    for(int i=0; i<n; i++)
    {
        cout<<num[i]<<" ";
    }

    // Display Numbers in Reverse Order as Output using Loop
    cout<<"\nDisplay in Reverse Order: ";
    for(int i=n-1; i>=0; i--)
    {
        cout<<num[i]<<" ";
    }
    return 0;
}