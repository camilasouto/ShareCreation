#ifndef FANITEM_H
#define FANITEM_H

#include <string>
#include <vector>

namespace web_api {

class FanItem {
private:
    std::string fanName;
    std::string fanUserName;
    std::string fanDateOfBirth;
    std::vector<std::string> listOfCreations;

public:
    FanItem(const std::string& fanName, const std::string& fanUserName, const std::string& fanDateOfBirth);
    void addCreation(const std::string& creation);
    std::vector<std::string> getCreations() const;
    std::string getFanName() const;
    std::string getFanUserName() const;
    std::string getFanDateOfBirth() const;
};

} // namespace web_api

#endif // FANITEM_H
