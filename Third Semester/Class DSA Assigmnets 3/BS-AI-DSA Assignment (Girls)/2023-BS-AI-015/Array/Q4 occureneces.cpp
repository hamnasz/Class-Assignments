#include <iostream>
using namespace std;
int main() {
    string arr[10];
    for (int i = 0; i < 10; i++)
	{
		cout<<"enter a character:";
        cin >> arr[i];
    }
    
    cout << "occurence count: " << endl;
    for (int i = 0; i < 10; i++) {
        int count = 1;
        for (int j = i + 1; j < 10; j++){
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > 1) {
        cout << arr[i] << " occurs " << count << " times" << endl;
        }
    }
    
}
