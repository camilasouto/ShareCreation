#include "CreationItem.h"

namespace web_api {

CreationItem::CreationItem(const std::string& name, const std::string& npuType, const std::string& userName, const std::string& timestamp)
    : creationName(name), creationNPUType(npuType), creationScore(0), userName(userName), timestamp(timestamp) {}

std::string CreationItem::getCreationName() const {
    return creationName;
}

std::string CreationItem::getNPUType() const {
    return creationNPUType;
}

int CreationItem::getScore() const {
    return creationScore;
}

bool CreationItem::setScore(int score, const std::string& token) {
    AuthorizationModule authModule;
    // Make sure the current user is not the creator of the creation
    if (authModule.verifyTokenBelongsToUser(token, userName)) {
        return false;
    }
    // Verify that the user is authorized to update the creation
    if (authModule.validateAuthorization(token, userName, CrudAction::ACTION_UPDATE)) {
        creationScore = score;
        return true;
    }
    return false;
}

std::vector<std::string> CreationItem::getHashTags() const {
    return creationHashTags;
}

bool CreationItem::addHashTag(const std::string& hashTag) {
    creationHashTags.push_back(hashTag);
    return true;
}

std::string CreationItem::getUserName() const {
    return userName;
}

std::string CreationItem::getTimestamp() const {
    return timestamp;
}

} // namespace web_api
