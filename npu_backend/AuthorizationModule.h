#ifndef AUTHORIZATIONMODULE_H
#define AUTHORIZATIONMODULE_H

#include <string>

namespace web_api {

enum class CrudAction {
    ACTION_CREATE = 0,
    ACTION_READ,
    ACTION_UPDATE,
    ACTION_DELETE
};

enum class AuthorizationLevel {
    AUTH_NONE = 0,
    AUTH_READ_OWN,
    AUTH_READ_OTHERS,
    AUTH_UPDATE_OWN,
    AUTH_UPDATE_OTHERS, 
    AUTH_DELETE_OWN,
    AUTH_DELETE_OTHERS,
    AUTH_CREATE_OWN,
    AUTH_CREATE_OTHERS
};

class AuthorizationModule {
public:
    bool validateAuthorization(const std::string& token, const std::string& userName, CrudAction action);
    bool verifyTokenBelongsToUser(const std::string& token, const std::string& userName);
    AuthorizationLevel getUserActionAuthorization(const std::string& token, CrudAction action);
};

} // namespace web_api

#endif // AUTHORIZATIONMODULE_H
