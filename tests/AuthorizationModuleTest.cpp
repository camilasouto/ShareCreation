#include <gtest/gtest.h>
#include "AuthorizationModule.h"

TEST(AuthorizationModuleTest, ValidateAuthorization) {
    web_api::AuthorizationModule authModule;
    std::string token = "valid_token";
    std::string userName = "user";

    EXPECT_TRUE(authModule.validateAuthorization(token, userName, web_api::CrudAction::ACTION_READ));
    EXPECT_FALSE(authModule.validateAuthorization(token, userName, web_api::CrudAction::ACTION_DELETE));
}

// Add more tests here
