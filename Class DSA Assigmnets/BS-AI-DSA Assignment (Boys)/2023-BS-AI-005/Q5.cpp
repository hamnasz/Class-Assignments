#include<iostream>
#include<string>
using namespace std;

int main(){
    string superheroes[5] = {"Superman", "Batman", "Spider-Man", "Wonder Woman", "Iron Man"};
    for(int i = 0; i < 5; i++){
        cout << superheroes[i] << endl;
    }
}