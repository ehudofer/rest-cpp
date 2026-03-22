#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "lib/httplib.h"
#include "lib/json.hpp"
#include "db.hpp"

using namespace std;
using json = nlohmann::json;

char _global_buffer[50 * 1024 * 1024];

int main(int argc, char* argv[]) {
    int port = 8080;
    if (argc > 1) {
        if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            cout << "Usage: " << argv[0] << " -p [port]" << endl;
            return 0;
        } else if (strcmp(argv[1], "-p") == 0 && argc > 2) {
            port = atoi(argv[2]); 
        }
    }

    httplib::Server svr;

    int counter = 0;

    DB& db = DB::getInstance();

    std::vector<User> users = db.getUsers();
    for (const auto& user : users) {
        std::cout << "User ID: " << user.id << ", Name: " << user.name <<  ", Email: " << user.email << ", Username: " << user.username << std::endl;
    }

    svr.Get("/js/:", [](const httplib::Request& req, httplib::Response& res) {
        std::string route = req.path;
        std::cout << "GET " << route << std::endl;
        std::ifstream file("html" + route, std::ios::in | std::ios::binary);
        if (file) {
            file.read(_global_buffer, sizeof(_global_buffer) - 1);
            std::streamsize bytesRead = file.gcount();
            _global_buffer[bytesRead] = '\0';
        } else {
            strcpy(_global_buffer, ("Failed to open " + route).c_str());
            std::cerr << _global_buffer << std::endl;
        }
        res.set_content(_global_buffer, "text/javascript");
    });

    svr.Get("/css/:", [](const httplib::Request& req, httplib::Response& res) {
        std::string route = req.path;
        std::cout << "GET " << route << std::endl;
        std::ifstream file("html" + route, std::ios::in | std::ios::binary);
        if (file) {
            file.read(_global_buffer, sizeof(_global_buffer) - 1);
            std::streamsize bytesRead = file.gcount();
            _global_buffer[bytesRead] = '\0';
        } else {
            strcpy(_global_buffer, ("Failed to open " + route).c_str());
            std::cerr << _global_buffer << std::endl;
        }
        res.set_content(_global_buffer, "text/css");
    });


    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        std::string route = req.path;
        std::cout << "GET " << route << std::endl;
        std::ifstream file("html/index.html", std::ios::in | std::ios::binary);
        if (file) {
            file.read(_global_buffer, sizeof(_global_buffer) - 1);
            std::streamsize bytesRead = file.gcount();
            _global_buffer[bytesRead] = '\0';
        } else {
            strcpy(_global_buffer, "Failed to open html/index.html");
        }
        res.set_content(_global_buffer, "text/html");
    });

    // svr.Post("/add", [](const httplib::Request& req, httplib::Response& res) {
    //     // if (req.get_header_value(""))
    //     // {
    //     //     /* code */
    //     // }
        
    //     string body = req.body;
    //     int sum = 0;
    //     res.set_content(body, "text/plain");
    // });
    svr.Post("/api/login", [&](const httplib::Request& req, httplib::Response& res) {
        std::string route = req.path;
        bool success = false;
        json response_json;
        std::cout << "POST " << route << std::endl;
        std::cout << "Request body: " << req.body << std::endl;
        try {
            json request_json = json::parse(req.body);
            std::string username = request_json["username"];
            std::string password = request_json["password"];
            std::vector<User> users = db.getUsers();
            for (const auto& user : users) {
                if (user.username == username && user.password == password) {
                    success = true;
                    response_json["id"] = user.id;
                    response_json["name"] = user.name;
                    response_json["email"] = user.email;
                    response_json["username"] = user.username;
                    response_json["assets"] = user.assets;
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            response_json["error"] = "Invalid JSON format";
            success = false;
        }
        if(success) {
            response_json["message"] = "Login successful";
            response_json["success"] = true;
        } else {
            response_json["message"] = "Invalid username or password";
            response_json["success"] = false;

        }
        res.set_content(response_json.dump(), "application/json");
    });
    svr.Get("/api/:", [&](const httplib::Request& req, httplib::Response& res) {
        std::string route = req.path;
        // std::cout << "GET " << route << std::endl;
        
        res.set_content(req.path + std::to_string(counter++), "text/html");
    });
    svr.listen("0.0.0.0", port);
    return 0;
}