#include "AuthorizationModule.h"

namespace web_api {

bool AuthorizationModule::validateAuthorization(const std::string& token, const std::string& userName, Action action) {
    // Placeholder authorization validation logic
    // Verify if user is allowed to perform the specified action
    return !token.empty() && token.find(userName) != std::string::npos;
}

bool AuthorizationModule::verifyTokenBelongsToUser(const std::string& token, const std::string& userName) {
    // Placeholder token verification logic
    return !token.empty() && token.find(userName) != std::string::npos;
}

} // namespace web_api
