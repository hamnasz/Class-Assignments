// Storing Students Data
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n, x=1;

    // Take Ammount of Students as Input from User
    cout<<"Enter Number of Students to Enter Data: ";
    cin>>n;

    // Declare and Initialize Arrays
    string name[n], department[n];
    int rollNo[n];

    // Take Students Data as Input from User using Loop
    for(int i=0; i<n; i++)
    {
        cout<<"Enter Student "<<x<<" Data!"<<endl;
        cout<<"Enter Name: ";
        cin>>name[i];
        cout<<"Enter Roll No: ";
        cin>>rollNo[i];
        cout<<"Enter Department: ";
        cin>>department[i];
        x++;
        cout<<endl;
    }
    x=1;

    // Display Students Data as Output using Loop
    for(int i=0; i<n; i++)
    {
        cout<<"Student "<<x<<" Data:"<<endl;
        cout<<"Name: "<<name[i]<<endl;
        cout<<"Roll No: "<<rollNo[i]<<endl;
        cout<<"Department: "<<department[i]<<endl;
        x++;
        cout<<endl;
    }
    return 0;
}