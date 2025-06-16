#include <iostream>
using namespace std;
int main()
{
    int size=0, arr[5] = {1, 2, 3, 4, 5};

    cout<<"Size of Each Element: "<<endl;
    for(int i=0; i<5; i++)
    {
        cout<<sizeof(arr[i])<<endl;
        size += sizeof(arr[i]);
    }
    cout<<"Total Array Size: "<<size;
    return 0;
}