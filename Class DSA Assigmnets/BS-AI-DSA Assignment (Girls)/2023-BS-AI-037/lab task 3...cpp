#include <iostream>
using namespace std;

int main() {
 int a[5];
 cout << "Enter the values of an integer array:" << endl;

 
 for (int i = 0; i < 5; ++i) {
 cin >> a[i];
 }

 cout << "Displaying integers:" << endl;

 
 for (int i = 0; i < 5; ++i) {
 cout << a[i] << endl;
 }
 return 0;
}