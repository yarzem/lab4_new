// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <header.hpp>

TEST(SharedPtr, value )
{
    otchet tmp;
    tmp.read_dir("/home/travis/build/yarzem/lab4_new/tests");
    EXPECT_EQ((std::string) checker["00001234"]._owner, "testdir");
    EXPECT_EQ((int) checker["00001346"]._count, 2);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
