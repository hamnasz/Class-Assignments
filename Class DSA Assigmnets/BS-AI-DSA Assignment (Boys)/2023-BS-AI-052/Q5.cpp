#include <iostream>
using namespace std;

int main()
{
    int n, num[10];

    cout<<"Enter any 10 Numbers:"<<endl;
    for(int i=0; i<10; i++)
    {
        cin>>num[i];
    }

    cout<<"Enter Number to Find: ";
    cin>>n;

    for(int i=0; i<10; i++)
    {
        if(n == num[i])
        {
            cout<<"Found at Index: "<<i<<endl;
        }
    }
    return 0;
}