#include<iostream>
#include<string>
using namespace std;

int main(){
    string movies[5] = {"Inception", "money heist", "Stranger things", "The Godfather", "Titanic"};
    for(int i = 0; i < 5; i++){
        cout << movies[i] << endl;
    }
}