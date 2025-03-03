#ifndef CREATIONCONTROLLER_H
#define CREATIONCONTROLLER_H

#include <string>
#include <map>
#include "CreationItem.h"

namespace web_api {

class CreationController {
private:
    std::map<std::string, CreationItem> creationsMap;

public:
    bool uploadCreation(const std::string& creationName, const std::string& npuType, const std::string& userName, const std::string& timestamp);
    CreationItem* findCreation(const std::string& creationName);
    bool deleteCreation(const std::string& creationName);
    const std::map<std::string, CreationItem>& getCreations() const { return creationsMap; }
};

} // namespace web_api

#endif // CREATIONCONTROLLER_H
