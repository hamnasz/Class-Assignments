#include<iostream>
#include<string>
using namespace std;

int main(){
    string pets[5] = {"Dog", "Cat", "Rabbit", "Parrot", "Hamster"};
    for(int i = 0; i < 5; i++){
        cout << pets[i] << endl;
    }
}