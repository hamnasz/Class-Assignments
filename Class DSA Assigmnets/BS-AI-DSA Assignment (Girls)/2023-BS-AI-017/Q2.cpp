// Print Size and Address of Each Array Element
#include <iostream>
using namespace std;
int main()
{
    int n=1, arr[5] = {1, 2, 3, 4, 5};

    // Display Size & Address of Each Element as Output
    cout<<"Size and Address of Each Element: "<<endl;
    for(int i=0; i<5; i++)
    {
        cout<<"Size & Address of Element "<<n<<": "<<endl;
        cout<<"Size: "<<sizeof(arr[i])<<endl;
        cout<<"Address: "<<&arr[i]<<endl;
        n++;
        cout<<endl;
    }
    return 0;
}