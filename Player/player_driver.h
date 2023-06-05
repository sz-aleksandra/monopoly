// Project: Monopoly
// Author: Jakub Bąba

#pragma once
#include <iostream>
#include <cctype>
#include <algorithm>
#include "player.h"

class PlayerDriver {
private:
    Player gamer;
public:
    PlayerDriver(Player &unit);
    void make_turn();
    void move();
    void buy_house_menu();

    void property_actions();
    void utility_actions();
    void station_actions();
    void start_actions();
    void tax_actions();
    void card_actions(std::string type);
    void wait_actions();
    void go_jail_actions();

    void buy_house();
    void buy_property();
};
