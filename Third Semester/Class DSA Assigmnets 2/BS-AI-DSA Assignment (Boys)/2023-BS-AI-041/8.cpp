#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector <string>Cities={"Karachi","Lahore","Multan","Quetta"};
	for(int i=0;i<4;i++){
		cout<<"City "<<i+1<<" : "<<Cities[i]<<endl;
	}
}