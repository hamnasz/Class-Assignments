#include <iostream>
#include <vector>
using namespace std;
int main(){
    vector<int> num;

    cout<<"Enter Numbers: "<<endl;
    for(int i=0; i<7; i++){
        int x;
        cin>>x;
        num.push_back(x);
    }

    cout<<"\nStored Order: ";
    for(int i=0; i<num.size(); i++){
        cout<<num[i]<<", ";
    }

    cout<<"\nReverse Order: ";
    for(int i=num.size()-1; i>=0; i--){
        cout<<num[i]<<", ";
    }
    return 0;
}