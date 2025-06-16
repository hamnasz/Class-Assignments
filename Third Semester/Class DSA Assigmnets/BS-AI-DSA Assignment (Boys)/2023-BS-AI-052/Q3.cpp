#include <iostream>
using namespace std;
int main()
{
    int sum =0, arr[5] = {15, 25, 9, 45, 3};

    for(int i=1; i<5; i++)
    {
        sum += arr[i];
    }
    
    int avg = sum / 5;
    cout<<"Average: "<<avg<<endl;
    return 0;
}