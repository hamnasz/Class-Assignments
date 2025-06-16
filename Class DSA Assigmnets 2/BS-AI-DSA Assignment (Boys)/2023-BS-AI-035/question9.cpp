#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector <string>Teachers={"Sir Hassan","Sir Jawad","Sir Javed","Sir Umer"};
	for(int i=0;i<4;i++){
		cout<<"Teacher "<<i+1<<" : "<<Teachers[i]<<endl;
	}
}