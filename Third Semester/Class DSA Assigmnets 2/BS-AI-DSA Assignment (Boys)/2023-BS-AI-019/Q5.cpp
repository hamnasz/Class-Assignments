// Searching a Number from Vector
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vec;
    int n, count;

    // Take Numbers as Input from User using Loop
    cout<<"Enter any 10 Numbers:"<<endl;
    for(int i=0; i<10; i++)
    {
        int x;
        cin>>x;
        vec.push_back(x);
    }

    // Take Number to Search as Input from User
    cout<<"Enter Number to Find: ";
    cin>>n;

    // Search and Display Index of Number using Loop
    for(int i=0; i<vec.size(); i++)
    {
        if(n == vec[i])
        {
            cout<<"Found at Index: "<<i<<endl;
            count++;
        }
    }
    cout<<"Total Occurencies: "<<count;
    return 0;
}