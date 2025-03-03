#ifndef CREATIONCONTROLLER_H
#define CREATIONCONTROLLER_H

#include <string>
#include <vector>
#include "CreationItem.h"

namespace web_api {

class CreationController {
public:
    std::vector<CreationItem> creations;

public:
    bool uploadCreation(const std::string& name, const std::string& npuType, const std::string& userName, const std::string& timestamp);
    CreationItem* findCreation(const std::string& name);
};

} // namespace web_api

#endif // CREATIONCONTROLLER_H
