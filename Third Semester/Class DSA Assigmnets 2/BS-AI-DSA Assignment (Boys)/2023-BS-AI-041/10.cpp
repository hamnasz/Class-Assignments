#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector <string>universities={"TUF","NUST","FAST","LUMS"};
	for(int i=0;i<4;i++){
		cout<<"University "<<i+1<<" : "<<universities[i]<<endl;
	}
}