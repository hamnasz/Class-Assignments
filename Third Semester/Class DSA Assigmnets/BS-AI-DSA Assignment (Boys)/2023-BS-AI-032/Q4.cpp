// beverage list
#include<iostream>
#include<string>
using namespace std;

int main(){
    string beverages[5] = {"Tea", "Coffee", "Juice", "Water", "Soda"};
    for(int i = 0; i < 5; i++){
        cout << beverages[i] << endl;
    }
}