#include<iostream>
using namespace std;
int main()
{
string arr[2][3] = {{"apple", "banana", "orange"},{"watermelon", "kiwi", "mango"}};
     for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << arr[i][j] << " "; 
        }
        cout << endl;
    }
}
