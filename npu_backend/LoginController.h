#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <string>

namespace web_api {

class LoginController {
public:
    std::string authenticate(const std::string& username, const std::string& password);
    bool validateToken(const std::string& token);

private:
    std::string generateToken(const std::string& username);
};

} // namespace web_api

#endif // LOGINCONTROLLER_H
