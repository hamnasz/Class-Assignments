#include<iostream>
using namespace std;

int maximum(int num[]){
    int maximum = num[0];
    for(int i=0; i<5; i++)
    {
        if(maximum < num[i]) {
            maximum = num[i];
        }
    }
    return maximum;
}

int miniimum(int num[])
{
    int miniimum = num[0];
    for(int i=0; i<5; i++) {
        if(miniimum > num[i]) {
            miniimum = num[i];
        }
    }
    return miniimum;
}

int main(){
    int num[5] = {5, 15, 17, 19, 28};
    
    // Display Output
    cout<<"maximumimum Number is: "<<maximum(num)<<endl;
    cout<<"miniimumimum Number is: "<<miniimum(num);
}