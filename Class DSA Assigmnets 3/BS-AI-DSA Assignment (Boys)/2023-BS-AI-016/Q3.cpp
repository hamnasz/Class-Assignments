
#include <iostream>
using namespace std;
int main(){

    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    cout<<"\nPrint in Stored Order: ";
    for(int i=0; i<8; i++){
        cout<<arr[i]<<", ";
    }

    cout<<"\nPrint in Reverse Order: ";
    for(int i=8-1; i>=0; i--){
        cout<<arr[i]<<", ";
    }
    return 0;
}