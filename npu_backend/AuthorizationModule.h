#ifndef AUTHORIZATIONMODULE_H
#define AUTHORIZATIONMODULE_H

#include <string>

namespace web_api {

enum class Action {
    CREATE,
    READ,
    UPDATE,
    DELETE
};

class AuthorizationModule {
public:
    bool validateAuthorization(const std::string& token, const std::string& userName, Action action);
    bool verifyTokenBelongsToUser(const std::string& token, const std::string& userName);
};

} // namespace web_api

#endif // AUTHORIZATIONMODULE_H
