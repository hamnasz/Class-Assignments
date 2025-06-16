// Storing Students Data
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n, x=1;

    // Take Ammount of Students as Input from User
    cout<<"Enter Amount of Students: ";
    cin>>n;

    // Declare and Initialize Arrays
    string name[n], fatherName[n], regNo[n], degree[n];

    // Take Students Data as Input from User
    for(int i=0; i<n; i++)
    {
        cout<<"Enter Student "<<x<<" Data!"<<endl;
        cout<<"Enter Name: ";
        cin>>name[i];
        cout<<"Enter Father Name: ";
        cin>>fatherName[i];
        cout<<"Enter Reg.No: ";
        cin>>regNo[i];
        cout<<"Enter Degree: ";
        cin>>degree[i];
        x++;
        cout<<endl;
    }
    x=1;

    // Display Students Data as Output
    for(int i=0; i<n; i++)
    {
        cout<<"Student "<<x<<" Data:"<<endl;
        cout<<"Name: "<<name[i]<<endl;
        cout<<"Name: "<<fatherName[i]<<endl;
        cout<<"Roll No: "<<regNo[i]<<endl;
        cout<<"Degree: "<<degree[i]<<endl;
        x++;
        cout<<endl;
    }
    return 0;
}