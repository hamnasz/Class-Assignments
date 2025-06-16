
#include <iostream>
using namespace std;

void countOccurences(char arr[], int count, int c)
{
    for(int i=0; i<10; i++){
        if(c == arr[i]){
            cout<<"Found at Index: "<<i<<endl;
            count++;
        }
    }
    cout<<"Total Occurencies: "<<count;
}
int main(){
    char arr[10], c;
    int count =0;

    cout<<"Enter any 10 Cahracters:"<<endl;
    for(int i=0; i<10; i++){
        cin>>arr[i];
    }

    cout<<"Enter Number to Find: ";
    cin>>c;

    countOccurences(10, arr, count, c);
    return 0;
}