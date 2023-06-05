#include <iostream>

#include "../monitor/reportaggregator.h"
#include "../monitor/reporter.h"
#include "../user/accountio.h"
#include "gtest/gtest.h"

class MonitorTest : public ::testing::Test {
protected:
    db::Database db;
    user::AccountIO aio;
    monitor::ReportAggregator ra;
    user::Account admin;

    MonitorTest() : db("../../database.sqlite"), aio((db::UserDB *)(&db)) {
        aio.pull(admin, 0);
        aio.verify(admin, "F1shApp!");
        ra = monitor::ReportAggregator(&admin, (db::MonitorDB *)(&db));
    }

    virtual ~MonitorTest() {
        // test deconstructor
    }
};

TEST_F(MonitorTest, AGGREGATOR_FETCH) {
    std::vector<monitor::MonitorItem *> vec;

    // all posts by username "sturgeot"
    vec = ra.fetch_among_posts(0, "sturgeot", 0);
    ASSERT_EQ((int)vec.size(), 1);
    ASSERT_EQ(vec.at(0)->get_item_id(), 39);

    // reported messages by phrase "fish"
    vec = ra.fetch_among_messages(4, "dogs", 1);
    ASSERT_EQ((int)vec.size(), 1);

    // all profiles by display name "Theodore Sturgeon"
    vec = ra.fetch_among_profiles(3, "Theodore Sturgeon", 0);
    ASSERT_EQ((int)vec.size(), 1);

    // too many possible permutations to show all, most effectively tested w/ ui
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
