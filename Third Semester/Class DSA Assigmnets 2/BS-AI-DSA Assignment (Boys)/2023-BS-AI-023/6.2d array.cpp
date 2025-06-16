#include<iostream>
using namespace std;
int main(){
	int n,m;
	int mx=INT_MIN;
	int mn=INT_MAX;
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
	for(int i=0;i<n;i++) {
	for (int j=0; j<m;j++) {
	mx=max(mx,arr[i][j]);
}	
}
	cout << "Maximum number is: " << mx << endl;
	for(int i=0;i<n;i++) {
	for (int j=0; j<m;j++) {
	mn=min(mn,arr[i][j]);
}	
}
	cout << "Minimum number is: " << mn << endl;
}