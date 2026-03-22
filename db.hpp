#ifndef DB_HPP
#define DB_HPP

#include <fstream>
#include "lib/json.hpp"

using json = nlohmann::json;

const std::string DB_FILE_NAME = "db.json";

struct User {
    int id;
    std::string name;
    std::string email;
    std::string username;
    std::string password;
    json assets;
};

class DB
{
private:
    DB();
    std::fstream _db_file;
    json _db_data;

public:
    static DB &getInstance();
    ~DB();
    User getUser(int idx) {
        User user{
        _db_data["users"][idx]["id"].get<int>(),
        _db_data["users"][idx]["name"].get<std::string>(),
        _db_data["users"][idx]["email"].get<std::string>(),
        _db_data["users"][idx]["username"].get<std::string>(),
        _db_data["users"][idx]["password"].get<std::string>(),
        _db_data["users"][idx]["assets"]
        };
        return user;
    }
    std::vector<User> getUsers();
    json& getData();
};


#endif // DB_HPP