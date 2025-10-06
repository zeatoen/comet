#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<optional>

/*
Name:package_name@version
Install using the same name
multiple versions can coexist in the venv but same package cannot depend
on same package of two different versions

dfs will return true if dependency cycle is detected
*/

std::optional<std::vector<std::string>> getDependency(const std::map<std::string, std::vector<std::string>>& adj) {
    std::set<std::string> visited;
    std::map<std::string, bool> inPath;
    std::vector<std::string> order;

    auto __dfs = [&](auto&& self, const std::string& node) -> bool {
        visited.insert(node);
        inPath[node] = true;

        if (adj.count(node)) {
            for (const auto& neighbor : adj.at(node)) {
                if (!visited.count(neighbor)) {
                    if (self(self, neighbor)) return true;
                } else if (inPath[neighbor]) {
                    return true;
                }
            }
        }

        inPath[node] = false;
        order.push_back(node);
        return false;
    };

    for (const auto& [node, _] : adj) {
        if (!visited.count(node)) {
            if (__dfs(__dfs, node)) {
                return std::nullopt;
            }
        }
    }

    std::reverse(order.begin(), order.end());
    return order;
}

std::map<std::string, std::vector<std::string>> Creategraph(const std::vector<std::pair<std::string,std::string>>& edges){
    std::map<std::string, std::vector<std::string>> adj;
    for(const auto &[u,v]:edges){
        adj[u].push_back(v);
    }
    return adj;
}
