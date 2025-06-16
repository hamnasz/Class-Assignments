#include<iostream>
#include<string>
using namespace std;

int main(){
    string games[5] = {"The Legend of Zelda", "Minecraft", "Fortnite", "Among Us", "Call of Duty"};
    for(int i = 0; i < 5; i++){
        cout << games[i] << endl;
    }
}