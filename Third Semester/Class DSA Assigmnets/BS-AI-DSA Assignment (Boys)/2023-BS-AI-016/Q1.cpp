#include <iostream>
using namespace std;
int main(){
    int sum =0, arr[5] = {1, 2, 3, 4, 5};

    for(int i=1; i<5; i++){
        sum += arr[i];
    }
    
    cout<<"Sum: "<<sum<<endl;
    return 0;
}