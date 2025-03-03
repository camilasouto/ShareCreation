#include "CreationController.h"

namespace web_api {

bool CreationController::uploadCreation(const std::string& name, const std::string& npuType, const std::string& userName, const std::string& timestamp) {
    creations.emplace_back(name, npuType, userName, timestamp);
    return true;
}

CreationItem* CreationController::findCreation(const std::string& name) {
    for (auto& creation : creations) {
        if (creation.getName() == name) {
            return &creation;
        }
    }
    return nullptr;
}

} // namespace web_api
