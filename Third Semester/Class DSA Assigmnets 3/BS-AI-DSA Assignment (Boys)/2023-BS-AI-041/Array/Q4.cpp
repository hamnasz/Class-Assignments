#include <iostream>
using namespace std;

int main(){
	int size = 5;
	char arr[size] = {'A','B','B','A','B'};
	for(int i = 0; i<size; i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	char ch;
	cout<<"Find Occurence: ";
	cin>>ch;
	int count = 0;
	for(int i = 0; i<size; i++){
		if(ch==arr[i]){
			count++;
		}
	}
	cout<<"Occurence: "<<count;
}