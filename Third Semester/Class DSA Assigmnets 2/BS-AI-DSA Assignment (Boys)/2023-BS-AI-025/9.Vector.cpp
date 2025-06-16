#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector <string>colleges={"PGC","Kips","Alley","TIPS"};
	for(int i=0;i<4;i++){
		cout<<"College "<<i+1<<" : "<<colleges[i]<<endl;
	}
}