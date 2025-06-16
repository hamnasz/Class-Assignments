#include<iostream>
using namespace std;

int max(int num[]){
    int max = num[0];
    for(int i=0; i<5; i++){
        if(max < num[i]){
            max = num[i];
        }
    }
    return max;
}

int min(int num[]){
    int min = num[0];
    for(int i=0; i<5; i++){
        if(min > num[i]){
            min = num[i];
        }
    }
    return min;
}

int main(){
    int num[5] = {12, 15, 86, 75, 14};
    
    cout<<"Max Number is: "<<max(num)<<endl;
     cout<<"Min Number is: "<<min(num);
}