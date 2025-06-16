#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector <int>scores={68,98,75,53,62};
	for(int i=0;i<4;i++){
		cout<<"Score "<<i+1<<" : "<<scores[i]<<endl;
	}
}