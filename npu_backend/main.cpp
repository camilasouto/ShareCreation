#include "LoginController.h"
#include "FanItem.h"
#include "CreationController.h"

#include "crow_all.h"
#include <cstdlib> // For std::getenv
using std::cout;

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "NPU Backend 1.0";
    });

    web_api::LoginController loginController;
    CROW_ROUTE(app, "/login").methods("POST"_method)([&loginController](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);

        std::string username = x["username"].s();
        std::string password = x["password"].s();

        std::string token = loginController.authenticate(username, password);
        if (!token.empty()) {
            crow::json::wvalue response;
            response["message"] = "Login successful";
            response["token"] = token;
            return crow::response(200, response);
        } else {
            crow::json::wvalue response;
            response["message"] = "Unauthorized";
            return crow::response(401, response);
        }
    });

    CROW_ROUTE(app, "/fan")([&loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto fanItem = web_api::FanItem::getInstance(token);
        crow::json::wvalue response;
        response["fanName"] = fanItem.getFanName();
        response["fanUserName"] = fanItem.getFanUserName();
        response["fanDateOfBirth"] = fanItem.getFanDateOfBirth();
        return crow::response(200, response);
    });

    CROW_ROUTE(app, "/fan/add").methods("POST"_method)([&loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);

        std::string fanName = x["fanName"].s();
        std::string fanUserName = x["fanUserName"].s();
        std::string fanDateOfBirth = x["fanDateOfBirth"].s();
        web_api::FanItem::createFan(fanName, fanUserName, fanDateOfBirth);
        return crow::response(200, "Fan created");
    });

    
    CROW_ROUTE(app, "/fan/creations")([&loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        std::string response = "";
        for (const auto& creation : web_api::FanItem::getInstance(token).getCreations()) {
            response += creation + "\n";
        }
        return crow::response(200, response);
    });
    CROW_ROUTE(app, "/fan/creations/add").methods("POST"_method)([&loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);

        std::string creation = x["creation"].s();
        if (web_api::FanItem::getInstance(token).addCreation(creation)) {
            return crow::response(200, "Creation added");
        } else {
            return crow::response(500, "Failed to add creation");
        }
    });

    web_api::CreationController creationController;
    CROW_ROUTE(app, "/creations")([&creationController, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        std::string response = "";
        for (const auto& creationPair : creationController.getCreations()) {
            response += creationPair.second.getCreationName() + "\n";
        }
        return crow::response(200, response);
    });
    CROW_ROUTE(app, "/creations/upload").methods("POST"_method)([&creationController, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);

        std::string name = x["name"].s();
        std::string npuType = x["npuType"].s();
        std::string userName = x["userName"].s();
        std::string timestamp = x["timestamp"].s();
        if (creationController.uploadCreation(name, npuType, userName, timestamp)) {
            return crow::response(200, "Creation uploaded");
        } else {
            return crow::response(500, "Failed to upload creation");
        }
    });
    CROW_ROUTE(app, "/creations/score").methods("POST"_method)([&creationController, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);

        std::string name = x["name"].s();
        int score = x["score"].i();
        web_api::CreationItem* creation = creationController.findCreation(name);
        if (creation) {
            if (creation->setScore(score, token)) {
                return crow::response(200, "Score updated");
            } else {
                return crow::response(403, "Forbidden");
            }
        } else {
            return crow::response(404, "Creation not found");
        }
    });
    CROW_ROUTE(app, "/creations/tags").methods("POST"_method)([&creationController, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);

        std::string name = x["name"].s();
        std::set<std::string> hashTags;
        for (const auto& tag : x["hashTags"].lo()) {
            hashTags.insert(tag.s());
        }
        web_api::CreationItem* creation = creationController.findCreation(name);
        if (creation) {
            for (const auto& hashTag : hashTags) {
                if (!creation->addHashTag(hashTag)) {
                    return crow::response(500, "Failed to add hash tag");
                }
            }
            return crow::response(200, "Hash tags added");
        } else {
            return crow::response(404, "Creation not found");
        }
    });

    CROW_ROUTE(app, "/creations/delete").methods("POST"_method)([&creationController, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);

        std::string creationName = x["creationName"].s();
        if (creationController.deleteCreation(creationName)) {
            return crow::response(200, "Creation deleted");
        } else {
            return crow::response(404, "Creation not found");
        }
    });

    CROW_ROUTE(app, "/creations/find_by_nputype").methods("GET"_method)([&creationController, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto npuType = req.url_params.get("npuType");
        if (!npuType) {
            return crow::response(400, "Missing npuType parameter");
        }
        std::string response = "";
        for (const auto& creation : creationController.findCreationsByNpuType(npuType)) {
            response += creation.getCreationName() + "\n";
        }
        return crow::response(200, response);
    });

    // Get the port from the environment variable or use 8888 as default
    const char* port = std::getenv("PORT");
    uint16_t portNumber = port ? std::stoi(port) : 8888;

    app.port(portNumber).run();
}
