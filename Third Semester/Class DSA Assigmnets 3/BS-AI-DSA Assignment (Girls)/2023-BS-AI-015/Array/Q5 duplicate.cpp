#include<iostream>
using namespace std;
int main ()
{
    int arr[10], i, j, k = 0;
    cout<<"enter elements of array : ";
    for(i=0; i<10; i++)
        cin>>arr[i];    
    for(i=0; i<10; i++){
        for(j=0; j<k; j++){
            if(arr[i]==arr[j])
                break;
        }
        if(j==k){
            arr[k]=arr[i];
            k++;
        }
    }
    cout << "repeated elements after deletion : ";
    for(i=0; i<k; i++)
        cout<<arr[i]<<" ";
}
