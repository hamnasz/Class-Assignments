#include<iostream>
using namespace std;
int main(){
	int n,m,order;
	cout<<"Enter rows: ";
	cin>>n;
	cout<<"Enter coloumns: ";
	cin>>m;
	int arr[n] [m];
	cout<<"Enter elements: ";
	for(int i=0;i<n;i++) {
	for (int j=0;j<m;j++) {
	cin>> arr[i][j];
}
}
	cout<<"Matrix is: "<<endl;
	for(int i=0;i<n;i++) {
	for (int j=0; j<m;j++) {
	cout<<arr[i][j]<<" ";
}
	cout<<"\n";
}
	order= n*m;
	cout<<"Order of matrix is: "<<order;
}