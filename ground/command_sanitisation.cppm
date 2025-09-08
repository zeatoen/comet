export module command_sanitisation;
import <cstring>;
import <cstdlib>;
import <filesystem>;
import <iostream>;
import <string>;
import <vector>;

// safety macros
#define MAX_ARGLEN 100

export struct config {
  enum actions { install, create_env, remove, no_action } action=config::no_action;
  std::string root = "";
  std::vector<std::string> envlist;
  std::vector<std::string> packages;
  std::string env_name = "";

};
export config main_config;

export void print_usage(){
  std::cerr<<"USAGE: comet [-i|-n] envname/package(s)"<<std::endl;
}
export bool init_conf(int argc, char **argv) {

  bool r_pkgs=false;
  bool r_env_name=false;
  for (int i = 1; i < argc; i++) {
    if (0 == strncmp(argv[i], "-i", MAX_ARGLEN)) {
    	if(main_config.action!=config::no_action){

    		return false;
    	}
    	main_config.action= config::actions::install;
      r_pkgs = true;
    } else if (0 == strncmp(argv[i], "-n", MAX_ARGLEN)) {
    	if(main_config.action!=config::no_action){
    		return false;
    	}
    	main_config.action=config::create_env;
      // r_pkgs = false;
      r_env_name = true;
    } else if (r_pkgs)
      main_config.packages.push_back(argv[i]);
    else if (r_env_name) {
      main_config.env_name = argv[i];
      r_env_name = false;
    } else {
      return false;
    }
  }
  if(main_config.action==config::no_action){
    return false;
  }

  std::string root = std::getenv("COMET_ROOT");
  if (root == "" && main_config.action != config::actions::create_env) {
    std::cerr << "run source script first.!" << std::endl;
    return false;
  };
  if (!std::filesystem::exists( std::filesystem::path(root))){
    return false;
  }

  return true;
}

