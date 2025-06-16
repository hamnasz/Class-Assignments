#include<iostream>
#include<string>
using namespace std;

int main(){
    string instruments[5] = {"Guitar", "Piano", "Violin", "Drums", "Flute"};
    for(int i = 0; i < 5; i++){
        cout << instruments[i] << endl;
    }
}