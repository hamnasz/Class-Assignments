#include <iostream>
using namespace std;
int main(){
    int size = 10;
    int sum =0, arr[size] = {1, 16, 4, 86, 3, 9, 17, 16, 25, 17};

    for(int i=0; i<size; i++){
        sum += arr[i];
    }
    cout<<"Sum:"<<sum<<endl;

    int avg = sum / size;
    cout<<"Average: "<<avg;
    return 0;
}