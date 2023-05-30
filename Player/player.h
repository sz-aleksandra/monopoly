// Project: Monopoly
// Author: Jakub Bąba

#pragma once
#include <iostream>
#include <set>
#include "custom_exceptions.h"

class Player {
private:
    std::string name;
    int money;
    int position;   // on board
    std::set<int> properties;
    bool in_jail;
    bool alive;
    std::string player_type; // human/bot

public:
    Player(std::string name_input, std::string type="human");

    // setters and typical changing properties
    void change_name(std::string name_input);
    void add_money(int amount);
    void take_money(int amount);
    void move_player(int amount);
    void set_position(int new_location);
    void add_property(int index);
    void remove_property(int index);
    void put_in_jail();
    void put_out_of_jail();
    void kill_player();
    void set_player_alive();

    // getters
    std::string get_name();
    int get_money();
    int get_position();
    bool has_property(int index);
    bool is_in_jail();
    bool is_alive();

    // miscellaneous
    void player_description();
};