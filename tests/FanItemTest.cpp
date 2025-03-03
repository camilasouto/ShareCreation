#include <gtest/gtest.h>
#include "FanItem.h"

TEST(FanItemTest, AddCreation) {
    web_api::FanItem fanItem = web_api::FanItem::createFan("FanName", "FanUserName", "01/01/1970");
    std::string creation = "NewCreation";

    EXPECT_TRUE(fanItem.addCreation(creation));
    EXPECT_EQ(fanItem.getCreations().size(), 1);
    EXPECT_EQ(fanItem.getCreations()[0], creation);
}

// Add more tests here
