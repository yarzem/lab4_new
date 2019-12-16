// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>

TEST(SharedPtr, value )
{
    otchet tmp;
    tmp.read_dir(".");
    EXPECT_EQ((std::string) checker["00001234"]._owner, "testdir");
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
