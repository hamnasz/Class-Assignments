#include<iostream>
using namespace std;
int main(){
	string grade[4]={"A", "C", "B", "A"};
	string subjects[4]={"AI", "Data STructure", "Software Engineering", "OOP"};
	for(int i=0; i<4; i++){
		cout<<subjects[i]<<" "<<grade[i]<<endl;
	}
}
