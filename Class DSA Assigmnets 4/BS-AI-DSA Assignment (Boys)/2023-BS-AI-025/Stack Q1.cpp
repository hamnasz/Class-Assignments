#include<iostream>
#include<string>
#include<stack>
using namespace std;
int main(){
	stack<string>bikes;
	bikes.push("CD70");
	bikes.push("Pridor");
	bikes.push("Suzuki 110");
	bikes.push("Yamaha");
	bikes.pop();
	bikes.pop();
	cout<<"Size of stack is: "<<bikes.size()<<"\n";
	cout<<"Top element in stack is: "<<bikes.top();
  	if(bikes.empty()==true){
  		cout<<"\nStack is empty";
	  }
	else
		cout<<"\nStack is not empty";
}