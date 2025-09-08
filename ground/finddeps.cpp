#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <json/reader.h>
#include <json/value.h>
#include <ostream>
#include <sstream>
#include <string>
#include <optional>
using namespace std;
const string  root="./repo";


bool does_ver_match(string ac, string mi, string ma){
	array<int, 3> ac_v,mi_v,ma_v;
	auto getver  = [](array<int,3>& v,string vs){
		istringstream is(vs);
		int f1,f2,f3;
		char c;
		is>>v[0]>>c>>v[1]>>c>>v[2];
	};
	getver(ac_v, ac);
	getver(ma_v, ma);
	getver(mi_v, mi);
	bool ok=true;
	for(int i=0;i<3;i++){
		if (mi_v[i]>ac_v[i] ||ma_v[i]<ac_v[i] ){
			ok=false;
			break;
		}
	}
		
	cout<<ok<<endl;
	return  ok;
}
optional<Json::Value> getpackage(string packagename, string minver, string maxver){
	filesystem::path root_dir(root);
	if(! filesystem::exists(root_dir) || !filesystem::is_directory(root_dir)){
		return nullopt;
	}
	for(auto &dir : filesystem::directory_iterator(root_dir)){
		istringstream is( dir.path().filename().generic_u8string());
		string name , version;
		is>>name>>version;
		cout<< name<<","<<version<<endl;
		if( name==packagename && does_ver_match(version, minver,maxver)){
			ifstream f(dir.path().string()+"/package.json");
			Json::Value retval;
			Json::parseFromStream(Json::CharReaderBuilder(), f ,&retval, nullptr);
			
			return retval;
		}
	}
	cout<<"here"<<endl;
	return nullopt;
}
