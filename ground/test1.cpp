#include "finddeps.cpp"
#include <json/json.h>
#include <json/writer.h>
#include <optional>
int main(){
	auto x = getpackage("abc","0.0.0","2.0.0");
	if(x!=nullopt)
		cout<< x.value()<<endl;
	else
		cout<<"nullopt"<<endl;
	return 0;
}