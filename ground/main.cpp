
import command_sanitisation;
import <iostream>;

using namespace std;
int main(int argc, char **argv) {
  if(!init_conf(argc, argv)){
    print_usage();
    return 1;
  }
  if(main_config.action==config::install){
    cout<<"Packages to insatll"<<endl;
    for(const auto& x :   main_config.packages){
      cout<<"\t"<<x <<endl;
    }
  }else if(main_config.action==config::create_env){
    cout<<"env name: "<<main_config.env_name<<endl;
  }
  // cerr<<"Everything is fine!!"<<endl;
  return 0;

}