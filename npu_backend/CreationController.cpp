#include "CreationController.h"

namespace web_api {

bool CreationController::uploadCreation(const std::string& creationName, const std::string& npuType, const std::string& userName, const std::string& timestamp) {
    creationsMap.emplace(creationName, CreationItem(creationName, npuType, userName, timestamp));
    return true;
}

CreationItem* CreationController::findCreation(const std::string& creationName) {
    auto it = creationsMap.find(creationName);
    if (it != creationsMap.end()) {
        return &it->second;
    }
    return nullptr;
}

bool CreationController::deleteCreation(const std::string& creationName) {
    return creationsMap.erase(creationName) > 0;
}

} // namespace web_api
