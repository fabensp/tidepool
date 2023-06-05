#include <iostream>

#include "gtest/gtest.h"
#include "log.h"

class LogTest : public ::testing::Test {
protected:
    Log s1;
    Log s2;
};

TEST_F(LogTest, LOG_INIT_FILENAME) {
    ASSERT_EQ(s1.get_filename(), "log.txt");
}

TEST_F(LogTest, LOG_CLOSE) {
    ASSERT_EQ(s1.get_state(), 'o');
    s1.close();
    ASSERT_EQ(s1.get_state(), 'c');
}

TEST_F(LogTest, LOG_OPEN_APPEND) {
    s1.close();
    ASSERT_EQ(s1.get_state(), 'c');
    s1.open_append("log2.txt");
    ASSERT_EQ(s1.get_filename(), "log2.txt");
    ASSERT_EQ(s1.get_state(), 'o');
    s1 << "test!\n";
}

TEST_F(LogTest, LOG_OPEN_OVERWRITE) {
    s1.close();
    ASSERT_EQ(s1.get_state(), 'c');
    s1.open_overwrite("log2.txt");
    ASSERT_EQ(s1.get_filename(), "log2.txt");
    ASSERT_EQ(s1.get_state(), 'o');
    s1 << "test!\n";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
