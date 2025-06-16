#include <iostream>
#include<vector>
using namespace std;
int main(){
	vector<string>cities={"Lahore,Karachi,Islamabad,Sialkot"};
	cities.push_back("Faisalabad");
	for(string city:cities){
		cout<<city<<"\n";
	}
	return 0;
}