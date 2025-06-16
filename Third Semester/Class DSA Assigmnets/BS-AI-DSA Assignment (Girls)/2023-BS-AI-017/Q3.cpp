// Arithmetic Operations using Array
#include <iostream>
using namespace std;
int main()
{
    int n;
    cout<<"Enter Amount of Numbers: ";
    cin>>n;

    int num[n];

    // Take Numbers as Input from User using Loop
    cout<<"Enter Numbers! "<<endl;
    for(int i=0; i<n; i++)
    {
        cin>>num[i];
    }

    int sum = num[0];
    int sub = num[0];
    int mul = num[0];
    float div = num[0];

    // Perform all Arithmetic Operations using Loop
    for(int i=1; i<n; i++)
    {
        sum += num[i];
        sub -= num[i];
        mul *= num[i];
        div /= num[i];
    }

    // Display Output
    cout<<"Sum: "<<sum<<endl;
    cout<<"Subtraction: "<<sub<<endl;
    cout<<"Multiplication: "<<mul<<endl;
    cout<<"Division: "<<div;
    return 0;
}