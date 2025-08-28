#include<arith.hpp>
#include <iostream>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	auto i = arith::add(a,b);
	
	if (i==nullopt){
		cerr<<"overflow"<<endl;
		return 1;
	}
	cout<<i.value()<<endl;
}