#include<iostream>
#include<string>
using namespace std;

int main(){
    string landmarks[5] = {"Eiffel Tower", "Great Wall of China", "Taj Mahal", "Statue of Liberty", "Colosseum"};
    for(int i = 0; i < 5; i++){
        cout << landmarks[i] << endl;
    }
}