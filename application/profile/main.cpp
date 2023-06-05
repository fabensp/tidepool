#include "profileio.h"
#include "gtest/gtest.h"
#include<algorithm>
#include <iostream>

class ProfileTest : public ::testing::Test {
protected:
    db::ProfileDB db;
    profile::ProfileIO pio;

    ProfileTest() : db("../../database.sqlite"), pio(&db) {}

    virtual ~ProfileTest() {}
};

class ProfileIOTest : public ::testing::Test {

protected:
    ProfileIOTest() : db("../../database.sqlite"), pio((db::ProfileDB*)&db), aio((db::UserDB*)&db) {}

    virtual ~ProfileIOTest() {}
    db::Database db;
    profile::ProfileIO pio;
    user::AccountIO aio;
};

TEST_F(ProfileIOTest, PIO_PULLING) {
    //Test pulling a profile with a id from the database
    profile::Profile p;
    ASSERT_EQ(pio.pull_profile_id(p, 0), 1);
    ASSERT_EQ(p.get_id(), 0);
    ASSERT_EQ(p.get_avatar_id(), 0);
    ASSERT_EQ(p.get_display_name(), "Theodore Sturgeon");
    ASSERT_EQ(p.get_bio(), "App creator");
    ASSERT_EQ(p.get_fish_date(), "1993-05-02");
    ASSERT_EQ(p.get_theme(), 2);

    profile::Profile p2;
    ASSERT_EQ(pio.pull_profile_id(p2, 1), 1);
    ASSERT_EQ(p2.get_id(), 1);
    ASSERT_EQ(p2.get_avatar_id(), 1);
    ASSERT_EQ(p2.get_display_name(), "Emma Roberts");
    ASSERT_EQ(p2.get_bio(), "I love fish!");
    ASSERT_EQ(p2.get_fish_date(), "2013-12-25");
    ASSERT_EQ(p2.get_theme(), 7);

    profile::Profile p6;
    ASSERT_EQ(pio.pull_profile_id(p6, 2), 1);
    ASSERT_EQ(p6.get_id(), 2);
    ASSERT_EQ(p6.get_avatar_id(), 0);
    ASSERT_EQ(p6.get_display_name(), "Oliver White");
    ASSERT_EQ(p6.get_bio(), "Just got an aquarium");
    ASSERT_EQ(p6.get_fish_date(), "2014-01-01");
    ASSERT_EQ(p6.get_theme(), 0);

    //Tests pals for this profile
    profile::Pal* pal_1 = p.get_pal(0);
    ASSERT_EQ(pal_1->get_id(), 0);
    ASSERT_EQ(pal_1->get_avatarId(), 3);
    ASSERT_EQ(pal_1->get_name(), "Bubbles");
    ASSERT_EQ(pal_1->get_species(), "Betta fish");
    ASSERT_EQ(pal_1->get_bio(),  "Bubbles is a feisty fish who loves to explore her tank and show off her beautiful fins.");
    profile::Pal* pal_2 = p.get_pal(1);
    ASSERT_EQ(pal_2->get_id(), 1);
    ASSERT_EQ(pal_2->get_avatarId(), 2);
    ASSERT_EQ(pal_2->get_name(), "Finn");
    ASSERT_EQ(pal_2->get_species(), "Neon tetra");
    ASSERT_EQ(pal_2->get_bio(),  "Finn is a curious fish who loves to swim around with his school and play hide-and-seek with his tank mates.");

    //Test pulling shoal tags
    vector<string> tags_ = p.get_shoal_membership();
    ASSERT_EQ(tags_[0], "Aquascaping");
    ASSERT_EQ(tags_[1], "Betta Fish");

    //Test links
    vector<string> labels_ = p.get_link_labels();
    vector<string> addresses_ = p.get_link_addresses();
    ASSERT_EQ(labels_[0], "LinkedIn");
    ASSERT_EQ(addresses_[0], "https://www.linkedin.com/");
    ASSERT_EQ(labels_[1], "Twitter");
    ASSERT_EQ(addresses_[1], "https://twitter.com/");
    ASSERT_EQ(labels_[2], "Website");
    ASSERT_EQ(addresses_[2], "https://www.google.com/");

    //Test pulling a reef
    vector<user::Account> reef_ = p.get_reef();
    user::Account u_ = reef_[0];
    ASSERT_EQ(u_.get_id(), 1);
    user::Account u2_ = reef_[1];
    ASSERT_EQ(u2_.get_id(), 2);
    user::Account u3_ = reef_[2];
    ASSERT_EQ(u3_.get_id(), 3);

    //Test pulling a profile with a display name from the database
    profile::Profile p3;
    ASSERT_EQ(pio.pull_profile_display_name(p3, "Theodore Sturgeon"), 1);
    ASSERT_EQ(p3.get_id(), 0);
    ASSERT_EQ(p3.get_avatar_id(), 0);
    ASSERT_EQ(p3.get_display_name(), "Theodore Sturgeon");
    ASSERT_EQ(p3.get_bio(), "App creator");
    ASSERT_EQ(p3.get_fish_date(), "1993-05-02");
    ASSERT_EQ(p3.get_theme(), 2);

    profile::Profile p4;
    ASSERT_EQ(pio.pull_profile_display_name(p4, "Emma Roberts"), 1);
    ASSERT_EQ(p4.get_id(), 1);
    ASSERT_EQ(p4.get_avatar_id(), 1);
    ASSERT_EQ(p4.get_display_name(), "Emma Roberts");
    ASSERT_EQ(p4.get_bio(), "I love fish!");
    ASSERT_EQ(p4.get_fish_date(), "2013-12-25");
    ASSERT_EQ(p4.get_theme(), 7);
}

TEST_F(ProfileIOTest, PIO_EDITING) {
    //Test editing the display name
    //p tests the class and p2 tests to make sure it updated the db
    profile::Profile p;
    pio.pull_profile_id(p, 1);
    ASSERT_EQ(p.get_display_name(), "Emma Roberts");
    pio.edit_display_name(p, "Dan Webber");
    ASSERT_EQ(p.get_display_name(), "Dan Webber");
    profile::Profile p2;
    pio.pull_profile_id(p2, 1);
    ASSERT_EQ(p2.get_display_name(), "Dan Webber");
    pio.edit_display_name(p, "Emma Roberts");


    //Test editing the avatar_id
    ASSERT_EQ(p.get_avatar_id(), 1);
    pio.edit_avatar_image(p, 2);
    ASSERT_EQ(p.get_avatar_id(), 2);
    pio.pull_profile_id(p2, 1);
    ASSERT_EQ(p2.get_avatar_id(), 2);
    pio.edit_avatar_image(p, 1);

    //Test chaning the bio
    ASSERT_EQ(p.get_bio(), "I love fish!");
    pio.edit_bio(p, "I love fish! This is new");
    ASSERT_EQ(p.get_bio(), "I love fish! This is new");
    pio.pull_profile_id(p2, 1);
    ASSERT_EQ(p2.get_bio(), "I love fish! This is new");
    pio.edit_bio(p, "I love fish!");

    //Test chaning the fishday
    ASSERT_EQ(p.get_fish_date(), "2013-12-25");
    pio.edit_fish_date(p, "2014-12-25");
    ASSERT_EQ(p.get_fish_date(), "2014-12-25");
    pio.pull_profile_id(p2, 1);
    ASSERT_EQ(p2.get_fish_date(), "2014-12-25");
    pio.edit_fish_date(p, "2013-12-25");

    //Test chaning the theme
    ASSERT_EQ(p.get_theme(), 7);
    pio.edit_theme(p, 5);
    ASSERT_EQ(p.get_theme(), 5);
    pio.pull_profile_id(p2, 1);
    ASSERT_EQ(p2.get_theme(), 5);
    pio.edit_theme(p, 7);
}

TEST_F(ProfileIOTest, PIO_EDITING_SHOAL_REEF) {
    //p is for class p2 is for database tests
    profile::Profile p;
    pio.pull_profile_id(p, 21);

    //Test shoal adding and removing
    pio.add_shoal_membership(p, "Freshwater Tank Tetras");
    vector<string> shoal = p.get_shoal_membership();
    ASSERT_EQ(shoal.size(), 2);
    ASSERT_EQ(shoal[1], "Freshwater Tank Tetras");
    profile::Profile p2;
    pio.pull_profile_id(p2, 21);
    vector<string> shoal2 = p2.get_shoal_membership();
    ASSERT_EQ(shoal2.size(), 2);
    ASSERT_EQ(shoal[1], "Freshwater Tank Tetras");
    pio.remove_shoal_membership(p, "Freshwater Tank Tetras");
    vector<string> shoal3 = p.get_shoal_membership();
    ASSERT_EQ(shoal3.size(), 1);
    pio.pull_profile_id(p2, 21);
    vector<string> shoal4 = p2.get_shoal_membership();
    ASSERT_EQ(shoal4.size(), 1);

    //Test reef adding and removing
    user::Account from;
    user::Account to;
    aio.pull(from, 0);
    aio.pull(to, 4);
    pio.pull_profile_id(p, 0);
    pio.add_user_to_reef(p, from, to);
    vector<user::Account> r = p.get_reef();
    ASSERT_EQ(r.size(), 5);

    pio.remove_reef(p, from, to);
    pio.pull_profile_id(p, 0);
    vector<user::Account> r2 = p.get_reef();
    ASSERT_EQ(r2.size(), 4);
}

TEST_F(ProfileIOTest, PIO_PAL) {
    //Test creating a pal
    profile::Profile p;
    pio.pull_profile_id(p, 21);
    pio.create_pal(p, 0, "Richard", "bass", "3/23/2003", "I am a happy fish.");
    pio.pull_pals(p);
    profile::Pal* pal = p.get_pal(0);
    ASSERT_EQ(pal->get_id(), 69);
    ASSERT_EQ(pal->get_avatarId(), 0);
    ASSERT_EQ(pal->get_name(), "Richard");
    ASSERT_EQ(pal->get_species(), "bass");
    ASSERT_EQ(pal->get_birthday(), "3/23/2003");
    ASSERT_EQ(pal->get_bio(), "I am a happy fish.");
    profile::Profile p2;
    pio.pull_profile_id(p2, 21);
    pio.pull_pals(p2);
    profile::Pal* pal2 = p2.get_pal(0);
    ASSERT_EQ(pal2->get_id(), 69);
    ASSERT_EQ(pal2->get_avatarId(), 0);
    ASSERT_EQ(pal2->get_name(), "Richard");
    ASSERT_EQ(pal2->get_species(), "bass");
    ASSERT_EQ(pal2->get_birthday(), "3/23/2003");
    ASSERT_EQ(pal2->get_bio(), "I am a happy fish.");

    //Test editing a pal
    //avatar_id
    profile::Profile p3;
    pio.pull_profile_id(p3, 21);
    profile::Pal* pal3 = p3.get_pal(0);
    ASSERT_EQ(pal3->get_avatarId(), 0);
    pio.edit_pal_avatar_id(pal3, 1);
    ASSERT_EQ(pal3->get_avatarId(), 1);
    profile::Profile p4;
    pio.pull_profile_id(p4, 21);
    profile::Pal* pal4 = p4.get_pal(0);
    ASSERT_EQ(pal4->get_avatarId(), 1);
    pio.edit_pal_avatar_id(pal3, 0);

    //name
    pal3 = p3.get_pal(0);
    ASSERT_EQ(pal3->get_name(), "Richard");
    pio.edit_pal_name(pal3, "new name");
    ASSERT_EQ(pal3->get_name(), "new name");
    pio.pull_profile_id(p4, 21);
    pal4 = p4.get_pal(0);
    ASSERT_EQ(pal4->get_name(), "new name");
    pio.edit_pal_name(pal3, "Richard");

    //species
    pal3 = p3.get_pal(0);
    ASSERT_EQ(pal3->get_species(), "bass");
    pio.edit_pal_species(pal3, "new species");
    ASSERT_EQ(pal3->get_species(), "new species");
    pio.pull_profile_id(p4, 21);
    pal4 = p4.get_pal(0);
    ASSERT_EQ(pal4->get_species(), "new species");
    pio.edit_pal_species(pal3, "bass");

    //birthday
    pal3 = p3.get_pal(0);
    ASSERT_EQ(pal3->get_birthday(), "3/23/2003");
    pio.edit_pal_birthday(pal3, "4/23/2003");
    ASSERT_EQ(pal3->get_birthday(), "4/23/2003");
    pio.pull_profile_id(p4, 21);
    pal4 = p4.get_pal(0);
    ASSERT_EQ(pal4->get_birthday(), "4/23/2003");
    pio.edit_pal_birthday(pal3, "3/23/2003");

    //bio
    pal3 = p3.get_pal(0);
    ASSERT_EQ(pal3->get_bio(), "I am a happy fish.");
    pio.edit_pal_bio(pal3, "new bio");
    ASSERT_EQ(pal3->get_bio(), "new bio");
    pio.pull_profile_id(p4, 21);
    pal4 = p4.get_pal(0);
    ASSERT_EQ(pal4->get_bio(), "new bio");
    pio.edit_pal_bio(pal3, "I am a happy fish.");

    //test removing a pal
    pio.remove_pal(p, pal);
    pio.pull_pals(p);
    vector<profile::Pal*> pals = p.get_pals();
    ASSERT_EQ(pals.size(), 0);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
