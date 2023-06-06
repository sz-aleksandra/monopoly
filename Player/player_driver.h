// Project: Monopoly
// Author: Jakub Bąba

#pragma once
#include <iostream>
#include <cctype>
#include <algorithm>
#include "player.h"
#include "dices.h"

class PlayerDriver {
private:
    Player player;
    Hand hand;
public:
    PlayerDriver(Player &unit, Hand &roller);
    void make_turn();
    void move();
    void new_position_actions();
    void buy_house_menu();

    void property_actions();
    void utility_actions();
    void station_actions();
    void start_actions();
    void tax_actions();
    void card_actions(std::string type);
    void go_jail_actions();

    void change_position_actions(std::string type, int value, bool skip_start=false); // types are move and set
    void give_money_actions(int amount);
    void take_money_actions(int amount);

    void buy_house();
    void buy_property();
};
