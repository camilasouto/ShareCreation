#ifndef CREATIONITEM_H
#define CREATIONITEM_H

#include <string>
#include <vector>
#include "AuthorizationModule.h"

namespace web_api {

class CreationItem {
private:
    std::string creationName;
    std::string creationNPUType;
    int creationScore;
    std::vector<std::string> creationHashTags;
    std::string userName;
    std::string timestamp;

public:
    CreationItem(const std::string& name, const std::string& npuType, const std::string& userName, const std::string& timestamp);

    std::string getName() const;
    std::string getNPUType() const;
    int getScore() const;
    bool setScore(int score, const std::string& token);
    std::vector<std::string> getHashTags() const;
    bool addHashTag(const std::string& hashTag);
    std::string getUserName() const;
    std::string getTimestamp() const;
};

} // namespace web_api

#endif // CREATIONITEM_H
