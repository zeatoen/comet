#include<iostream>
#include"Header.hpp"

bool __install(const std::vector<std::string> &packages){
    for(const auto &s:packages){
        std::cout<<s<<' ';
    }
    std::cout<<'\n';
    return 1;
}

// 0 dependecy cycle, 2 some issue in installing
int install(const std::string& package,const std::string &version){
    const auto dependencies=__query(package,version);
    if(!dependencies){
        // cyclic dependencies
        return 0;
    }

    const auto &__dependencies=dependencies.value(); 
    auto adj=Creategraph(__dependencies);
    auto packages=getDependency(adj);

    if(__install(packages.value())){
        return 1;
    }
    return 2;
}

// int main() {
//     // Change this to a package and version that exists in your DB
//     std::string pkg = "pkgA";
//     std::string ver = "1.0";

//     int status = install(pkg, ver);

//     if (status == 0) {
//         std::cout << "❌ Dependency cycle detected.\n";
//     } else if (status == 1) {
//         std::cout << "✅ Package installed successfully.\n";
//     } else if (status == 2) {
//         std::cout << "⚠️ Error during installation.\n";
//     }

//     return 0;
// }