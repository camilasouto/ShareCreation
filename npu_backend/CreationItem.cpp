#include "CreationItem.h"

namespace web_api {

CreationItem::CreationItem(const std::string& name, const std::string& npuType)
    : creationName(name), creationNPUType(npuType), creationScore(0) {}

std::string CreationItem::getName() const {
    return creationName;
}

std::string CreationItem::getNPUType() const {
    return creationNPUType;
}

int CreationItem::getScore() const {
    return creationScore;
}

void CreationItem::setScore(int score) {
    creationScore = score;
}

std::vector<std::string> CreationItem::getHashTags() const {
    return creationHashTags;
}

void CreationItem::addHashTag(const std::string& hashTag) {
    creationHashTags.push_back(hashTag);
}

} // namespace web_api
