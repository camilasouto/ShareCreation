#include "LoginController.h"
#include "FanItem.h"
#include "CreationController.h"

#include "crow_all.h"
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

    web_api::FanItem fanItem("admin", "admin", "01/01/1970");
    CROW_ROUTE(app, "/fan")([&fanItem, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        return crow::response(200, fanItem.getFanName());
    });
    CROW_ROUTE(app, "/fan/creations")([&fanItem, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        std::string response = "";
        for (const auto& creation : fanItem.getCreations()) {
            response += creation + "\n";
        }
        return crow::response(200, response);
    });
    CROW_ROUTE(app, "/fan/creations/add").methods("POST"_method)([&fanItem, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);

        std::string creation = x["creation"].s();
        fanItem.addCreation(creation);
        return crow::response(200, "Creation added");
    });

    web_api::CreationController creationController;
    CROW_ROUTE(app, "/creations")([&creationController, &loginController](const crow::request& req){
        auto token = req.url_params.get("token");
        if (!token || !loginController.validateToken(token)) {
            return crow::response(401, "Unauthorized");
        }
        std::string response = "";
        for (const auto& creation : creationController.creations) {
            response += creation.getName() + "\n";
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
        creationController.uploadCreation(name, npuType);
        return crow::response(200, "Creation uploaded");
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
            creation->setScore(score);
            return crow::response(200, "Score updated");
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
        std::vector<std::string> hashTags;
        for (const auto& tag : x["hashTags"].lo()) {
            hashTags.push_back(tag.s());
        }
        web_api::CreationItem* creation = creationController.findCreation(name);
        if (creation) {
            for (const auto& hashTag : hashTags) {
                creation->addHashTag(hashTag);
            }
            return crow::response(200, "Hash tags added");
        } else {
            return crow::response(404, "Creation not found");
        }
    });

    app.port(8888).run();
}
