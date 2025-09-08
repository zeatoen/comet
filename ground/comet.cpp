
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// safety macros
#define MAX_ARGLEN 100

struct config {
  enum actions { install, create_env, remove, no_action } action;
  string root = "";
  vector<string> envlist;
  vector<string> packages;
  string env_name = "";

} main_config;

void print_usage(){

}
bool init_conf(int argc, char **argv) {

  bool r_pkgs;
  bool r_env_name;
  for (int i = 1; i < argc; i++) {
    if (0 == strncmp(argv[i], "-i", MAX_ARGLEN)) {
    	if(main_config.action!=config::no_action){
    		print_usage();

    		return false;
    	}
    	main_config.action= config::actions::install;
      r_pkgs = true;
    } else if (0 == strncmp(argv[i], "-n", MAX_ARGLEN)) {
    	if(main_config.action!=config::no_action){
    		print_usage();
    		return false;
    	}
    	main_config.action=config::create_env;
      r_env_name = true;
    } else if (r_pkgs)
      main_config.packages.push_back(argv[i]);
    else if (r_env_name) {
      main_config.env_name = argv[i];
      r_env_name = false;
    } else {
      print_usage();
      return false;
    }
  }
  // no issues.

  string root = getenv("COMET_ROOT");
  if (root == "" && main_config.action != config::actions::create_env) {
    cerr << "run source script first.!" << endl;
    return false;
  };
  // sanitze root.
  return true;
}

int main(int arcg, char **arcv) {}