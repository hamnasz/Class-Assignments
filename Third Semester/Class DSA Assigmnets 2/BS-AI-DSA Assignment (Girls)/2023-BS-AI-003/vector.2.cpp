#include <iostream>
#include<vector>
using namespace std;
int main(){
	vector<string>sports={"cricket,hockey,tennis"};
	sports.push_back("football");
	for(string sport:sports){
		cout<<sport<<"\n";
	}
	return 0;
}