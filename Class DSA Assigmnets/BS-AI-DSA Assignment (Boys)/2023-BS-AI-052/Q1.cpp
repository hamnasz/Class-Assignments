#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n= 3;
    string name[n], accountNo[n], balance[n];

    for(int i=0; i<n; i++)
    {
        cout<<"Enter Account Holder Data!"<<endl;
        cout<<"Enter Name: ";
        cin>>name[i];
        cout<<"Enter Account No: ";
        cin>>accountNo[i];
        cout<<"Enter Account Balance: ";
        cin>>balance[i];
        cout<<endl;
    }

    for(int i=0; i<n; i++)
    {
        cout<<"Account Holder Data:"<<endl;
        cout<<"Name: "<<name[i]<<endl;
        cout<<"Account No: "<<accountNo[i]<<endl;
        cout<<"Account Balance: "<<balance[i]<<endl;
        cout<<endl;
    }
    return 0;
}