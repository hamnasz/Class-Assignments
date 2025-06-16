#include <iostream>
#include <string>
using namespace std;
int main(){
    int n= 5;
    string car[n], model[n], company[n];

    for(int i=0; i<n; i++){
        cout<<"Enter Car Data!"<<endl;
        cout<<"Enter Car: ";
        cin>>car[i];
        cout<<"Enter Car Model: ";
        cin>>model[i];
        cout<<"Enter Car Company: ";
        cin>>company[i];
        cout<<endl;
    }

    for(int i=0; i<n; i++){
        cout<<"Car:"<<endl;
        cout<<"Car: "<<car[i]<<endl;
        cout<<"Car Model: "<<model[i]<<endl;
        cout<<"Car Company: "<<company[i]<<endl;
        cout<<endl;
    }
    return 0;
}