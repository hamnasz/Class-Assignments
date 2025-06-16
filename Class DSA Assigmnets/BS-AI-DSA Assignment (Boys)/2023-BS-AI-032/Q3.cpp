// music genres list
#include<iostream>
#include<string>
using namespace std;

int main(){
    string genres[5] = {"Rock", "Pop", "Jazz", "Classical", "Hip Hop"};
    for(int i = 0; i < 5; i++){
        cout << genres[i] << endl;
    }
}
