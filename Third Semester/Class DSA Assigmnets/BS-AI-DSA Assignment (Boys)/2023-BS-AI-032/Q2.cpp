#include<iostream>
#include<string>
using namespace std;

int main(){
    string books[5] = {"math", "data structure", "artificial intelligence", "urdu", "ENGLISH"};
    for(int i = 0; i < 5; i++){
        cout << books[i] << endl;
    }
}