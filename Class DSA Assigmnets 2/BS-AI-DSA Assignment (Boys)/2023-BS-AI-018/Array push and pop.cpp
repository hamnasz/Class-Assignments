#include <iostream>
#include <vector>
using namespace std;
int main(){
	vector<int> numbers;
	float input;
	
	
	cout<<"Enter any numbers: "<<endl;
	for(int i=0;i<5;i++){
			cin>>input;
		numbers.push_back(input);
	}
	
	cout<<"\n You have entered the following numbers: "<<endl;
	for(int i=0;i<numbers.size();i++){
		cout<<numbers[i]<<" "<<endl;
	}
	//remove a number
	 numbers.pop_back();

    // Display the modified vector
    cout << "Modified vector after pop_back(): ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

	return 0;
}