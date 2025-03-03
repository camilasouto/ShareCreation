#include <gtest/gtest.h>
#include "CreationController.h"

TEST(CreationControllerTest, UploadCreation) {
    web_api::CreationController creationController;
    std::string creationName = "TestCreation";
    std::string npuType = "TypeA";
    std::string userName = "user";
    std::string timestamp = "2023-10-01";

    EXPECT_TRUE(creationController.uploadCreation(creationName, npuType, userName, timestamp));
    EXPECT_NE(creationController.findCreation(creationName), nullptr);
}

// Add more tests here
