#include "CreationController.h"

namespace web_api {

void CreationController::uploadCreation(const std::string& name, const std::string& npuType) {
    creations.emplace_back(name, npuType);
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
