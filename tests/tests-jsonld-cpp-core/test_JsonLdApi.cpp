#include "JsonLdApi.cpp"
#include "testHelpers.h"

#include <gtest/gtest.h>

#ifndef _WIN32
#pragma clang diagnostic push
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma clang diagnostic pop
#pragma GCC diagnostic pop
#endif

TEST(JsonLdApiTest, construct_default) {
    JsonLdApi api;
    EXPECT_EQ(api.getOptions()->getBase(), "");
}

TEST(JsonLdApiTest, construct_with_options) {
    const auto options = std::make_shared<JsonLdOptions>("foobar");
    JsonLdApi api(options);
    EXPECT_EQ(api.getOptions()->getBase(), "foobar");
}



