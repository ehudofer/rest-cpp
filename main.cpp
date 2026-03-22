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
        std::cout << "User ID: " << user.id << ", Name: " << user.name << ", Email: " << user.email << std::endl;
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
    svr.Get("/api/:", [&](const httplib::Request& req, httplib::Response& res) {
        std::string route = req.path;
        // std::cout << "GET " << route << std::endl;
        
        res.set_content(req.path + std::to_string(counter++), "text/html");
    });
    svr.listen("0.0.0.0", port);
    return 0;
}