// Finding Maximum Number
#include<iostream>
using namespace std;

int max(int size, int num[])
{
    int max = num[0];
    for(int i=0; i<size; i++)
    {
        if(max < num[i])
        {
            max = num[i];
        }
    }
    return max;
}

int min(int size, int num[])
{
    int min = num[0];
    for(int i=0; i<size; i++)
    {
        if(min > num[i])
        {
            min = num[i];
        }
    }
    return min;
}

int main()
{
    int size = 5;
    int num[size] = {5, 15, 17, 19, 28};
    
    // Display Output
    cout<<"Maximum Number is: "<<max(size, num)<<endl;
     cout<<"Minimum Number is: "<<min(size, num);
}