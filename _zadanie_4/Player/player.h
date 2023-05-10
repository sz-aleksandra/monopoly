// Project: Monopoly
// Author: Jakub Bąba

#pragma once
#include <set>

class Player {
private:
    std::string name;
    int money;
    int position;   // on board
    std::set<int> properties;
    bool alive;

public:
    Player(std::string name_input);

    void change_name(std::string name_input);
    void add_money(int amount);
    void take_money(int amount);
    void move_player(int amount);
    void set_location(int new_location);
    void add_property(int index);
    void remove_property(int index);

    std::string get_name();
    int get_money();
    int get_location();
    bool has_property(int index);
    bool is_alive();

    // interactions
    void pay_to_other(Player receiver, int amount);

};