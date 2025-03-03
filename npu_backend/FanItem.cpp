#include "FanItem.h"

namespace web_api {

FanItem::FanItem(const std::string& fanName, const std::string& fanUserName, const std::string& fanDateOfBirth)
    : fanName(fanName), fanUserName(fanUserName), fanDateOfBirth(fanDateOfBirth) {}

bool FanItem::addCreation(const std::string& creation) {
    listOfCreations.push_back(creation);
    return true;
}

std::vector<std::string> FanItem::getCreations() const {
    return listOfCreations;
}

std::string FanItem::getFanName() const {
    return fanName;
}

std::string FanItem::getFanUserName() const {
    return fanUserName;
}

std::string FanItem::getFanDateOfBirth() const {
    return fanDateOfBirth;
}

} // namespace web_api
