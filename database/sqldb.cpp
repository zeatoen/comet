#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <optional>
#include <SQLiteCpp/SQLiteCpp.h>


void getEdgesForPackage(SQLite::Database& db, int package_id,
                        std::vector<std::pair<std::string, std::string>>& edges,
                        std::unordered_set<int>& visited) 
{
    if (visited.count(package_id)) return;
    visited.insert(package_id);

    SQLite::Statement query(db, R"(
        SELECT 
            p1.name || '@' || p1.version AS package,
            p2.name || '@' || p2.version AS dependency,
            d.dependency_id
        FROM Dependencies d
        JOIN Packages p1 ON d.package_id = p1.id
        JOIN Packages p2 ON d.dependency_id = p2.id
        WHERE d.package_id = ?
    )");

    query.bind(1, package_id);

    while (query.executeStep()) {
        std::string from = query.getColumn(0).getString();
        std::string to = query.getColumn(1).getString();
        int dep_id = query.getColumn(2).getInt();

        edges.emplace_back(from, to);

        // Recurse on the dependency package
        getEdgesForPackage(db, dep_id, edges, visited);
    }
}

std::optional<int> getPackageId(SQLite::Database& db, const std::string& name, const std::string& version)
{
    SQLite::Statement query(db, "SELECT id FROM Packages WHERE name = ? AND version = ?");
    query.bind(1, name);
    query.bind(2, version);

    if (query.executeStep()) {
        return query.getColumn(0).getInt();
    }
    return std::nullopt;
}

// Main API function: returns all edges reachable from the given package name@version
std::optional<std::vector<std::pair<std::string, std::string>>> getDependencyEdges(SQLite::Database& db, const std::string& name, const std::string& version)
{
    auto package_id_opt = getPackageId(db, name, version);
    if (!package_id_opt) {
        std::cerr << "Package " << name << "@" << version << " not found in database\n";
        return std::nullopt;
    }

    std::vector<std::pair<std::string, std::string>> edges;
    std::unordered_set<int> visited;

    getEdgesForPackage(db, *package_id_opt, edges, visited);

    return edges;
}

// Example 
std::optional<std::vector<std::pair<std::string, std::string>>> __query(const std::string &package, const std::string version) 
{
    try {
        SQLite::Database db("package.db", SQLite::OPEN_READONLY);

        auto edges_opt = getDependencyEdges(db, package, version);

        if (!edges_opt) {
            return std::nullopt;
        }

        return edges_opt;

    } catch (const std::exception& e) {
        std::cerr << "DB error: " << e.what() << "\n";
    }

    return std::nullopt;
}
