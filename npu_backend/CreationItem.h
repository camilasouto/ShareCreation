#ifndef CREATIONITEM_H
#define CREATIONITEM_H

#include <string>
#include <vector>

namespace web_api {

class CreationItem {
private:
    std::string creationName;
    std::string creationNPUType;
    int creationScore;
    std::vector<std::string> creationHashTags;

public:
    CreationItem(const std::string& name, const std::string& npuType);

    std::string getName() const;
    std::string getNPUType() const;
    int getScore() const;
    void setScore(int score);
    std::vector<std::string> getHashTags() const;
    void addHashTag(const std::string& hashTag);
};

} // namespace web_api

#endif // CREATIONITEM_H
