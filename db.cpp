#include "db.hpp"


DB::DB() : _db_file(DB_FILE_NAME, std::ios::in | std::ios::out | std::ios::app){
    // Initialize the database connection here
    _db_file.seekg(0);
    _db_data = json::parse(_db_file);
}

DB& DB::getInstance() {
    static DB instance;
    return instance;
}

DB::~DB() {
    // Clean up the database connection here
    _db_file.close();
}

std::vector<User> DB::getUsers() {
    std::vector<User> users;
    for (const auto& item : _db_data["users"]) {
        User user;
        user.id = item["id"].get<int>();
        user.name = item["name"].get<std::string>();
        user.email = item["email"].get<std::string>();
        user.password = item["password"].get<std::string>();
        user.assets = item["assets"];
        users.push_back(user);
    }
    return users;
}

json& DB::getData() {
    return _db_data;
}