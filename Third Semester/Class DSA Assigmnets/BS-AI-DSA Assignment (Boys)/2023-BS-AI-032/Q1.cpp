// planet list
#include<iostream>
#include<string>
using namespace std;

int main(){
    string planets[5] = {"Earth", "Mars", "Jupiter", "Saturn", "Venus"};
    for(int i = 0; i < 5; i++){
        cout << planets[i] << endl;
    }
}