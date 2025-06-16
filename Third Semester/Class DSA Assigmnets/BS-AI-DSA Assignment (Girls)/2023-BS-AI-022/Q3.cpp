#include<iostream>
#include<string>
using namespace std;

int main(){
    string juices[5] = {"Orange Juice", "Apple Juice", "Grape Juice", "Pineapple Juice", "Mango Juice"};
    for(int i = 0; i < 5; i++){
        cout << juices[i] << endl;
    }
}