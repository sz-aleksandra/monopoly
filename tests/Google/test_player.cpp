// Project: Histogram
// Author: Jakub Bąba

#include "gtest/gtest.h"
#include "../../Player/player.h"
#include "../../Player/player.cpp"


TEST(player_test, name) {
    Player a("aaa");
    ASSERT_EQ(a.get_name(), "aaa");

    a.change_name("Jakub");
    ASSERT_EQ(a.get_name(), "Jakub");

    EXPECT_THROW({
        a.change_name("");
        }, empty_name_exception);

    ASSERT_EQ(a.get_name(), "Jakub");
}


TEST(player_test, money) {
    Player a("aaa");
    ASSERT_EQ(a.get_money(), 1500);

    a.add_money(400);
    a.add_money(84);
    ASSERT_EQ(a.get_money(), 1984);

    a.take_money(1850);
    ASSERT_EQ(a.get_money(), 134);

    EXPECT_THROW({
        a.take_money(200);
        }, not_enough_money_exception);

    ASSERT_EQ(a.get_money(), 134);
}


TEST(player_test, position) {
    Player a("aaa");
    ASSERT_EQ(a.get_position(), 0);

    a.move_player(5);
    a.move_player(2);
    ASSERT_EQ(a.get_position(), 7);

    a.move_player(-10);
    ASSERT_EQ(a.get_position(), 37);

    a.move_player(4);
    ASSERT_EQ(a.get_position(), 1);

    a.set_position(21);
    ASSERT_EQ(a.get_position(), 21);

    EXPECT_THROW({
        a.set_position(40);
        }, position_outside_board_exception);
    ASSERT_EQ(a.get_position(), 21);
}


TEST(player_test, properties) {
    Player a("aaa");
    for (int i = 0; i < 40; i++)
        ASSERT_EQ(a.has_property(i), false);

    a.add_property(5);
    a.add_property(5);
    a.add_property(8);
    a.add_property(9);
    for (int i = 0; i < 40; i++) {
        if (i==5 || i==8 || i==9)
            ASSERT_EQ(a.has_property(i), true);
        else
            ASSERT_EQ(a.has_property(i), false);
    }

    a.remove_property(3);
    a.remove_property(9);
    a.remove_property(0);
    for (int i = 0; i < 40; i++) {
        if (i==5 || i==8)
            ASSERT_EQ(a.has_property(i), true);
        else
            ASSERT_EQ(a.has_property(i), false);
    }
}

TEST(player_test, jail) {
    Player a("aaa");
    ASSERT_EQ(a.is_in_jail(), false);

    a.put_in_jail();
    a.put_in_jail();
    a.put_in_jail();
    ASSERT_EQ(a.is_in_jail(), true);

    a.put_out_of_jail();
    ASSERT_EQ(a.is_in_jail(), false);
}


TEST(player_test, alive) {
    Player a("aaa");
    ASSERT_EQ(a.is_alive(), true);

    a.kill_player();
    a.kill_player();
    ASSERT_EQ(a.is_alive(), false);

    a.set_player_alive();
    ASSERT_EQ(a.is_alive(), true);
}

