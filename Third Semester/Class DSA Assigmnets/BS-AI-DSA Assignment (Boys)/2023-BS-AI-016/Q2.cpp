#include<iostream>
using namespace std;
int main(){
    int num[10];

    cout<<"Enter 10 Numbers:"<<endl;
    for(int i=0; i<10; i++){
        cin>>num[i];
    }

    cout<<"Even Numbers: ";
    for(int i=0; i<10; i++){
        if(num[i] % 2 == 0){
            cout<<num[i]<<" ";
        }
    }
    cout<<endl;

    cout<<"Odd Numbers: ";
    for(int i=0; i<10; i++){
        if(num[i] % 2 != 0){
            cout<<num[i]<<" ";
        }
    }
    return 0;
}