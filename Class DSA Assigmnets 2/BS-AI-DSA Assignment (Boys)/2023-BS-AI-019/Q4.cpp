// Reverse Number using Vector
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> vec;

    // Take Numbers as Input from User using Loop
    cout<<"Enter Numbers: "<<endl;
    for(int i=0; i<5; i++)
    {
        int x;
        cin>>x;
        vec.push_back(x);
    }

    // Display Numbers in Stored Order as Output using Loop
    cout<<"\nPrint in Stored Order: ";
    for(int i=0; i<vec.size(); i++)
    {
        cout<<vec[i]<<", ";
    }

    // Display Numbers in Reverse Order as Output using Loop
    cout<<"\nPrint in Reverse Order: ";
    for(int i=vec.size()-1; i>=0; i--)
    {
        cout<<vec[i]<<", ";
    }
    return 0;
}