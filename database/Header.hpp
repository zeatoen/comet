#include<vector>
#include<map>
#include<set>
#include<unordered_set>
#include<algorithm>
#include<optional>
#include <SQLiteCpp/SQLiteCpp.h>

std::map<std::string, std::vector<std::string>> Creategraph(const std::vector<std::pair<std::string,std::string>>& edges);
std::optional<std::vector<std::string>> getDependency(const std::map<std::string, std::vector<std::string>>& adj);
void getEdgesForPackage(SQLite::Database& db, int package_id,std::vector<std::pair<std::string, std::string>>& edges,std::unordered_set<int>& visited);
std::optional<std::vector<std::pair<std::string, std::string>>> getDependencyEdges(SQLite::Database& db, const std::string& name, const std::string& version);
std::optional<std::vector<std::pair<std::string, std::string>>> __query(const std::string &package,const std::string version);
