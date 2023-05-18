// Project: Monopoly
// Author: Jakub Bąba

#pragma once
#include <iostream>
#include <set>

class Player {
protected:
    std::string name;
    int money;
    int position;   // on board
    std::set<int> properties;
    bool in_jail;
    bool alive;

public:
    Player(std::string name_input);

    // setters and typical changing properties
    void change_name(std::string name_input);
    void add_money(int amount);
    void take_money(int amount);
    void move_player(int amount);
    void set_position(int new_location);
    void add_property(int index);
    void remove_property(int index);

    // getters
    std::string get_name();
    int get_money();
    int get_position();
    bool has_property(int index);
    bool is_in_jail();
    bool is_alive();

    // interactions
    void pay_to_other(Player receiver, int amount);
    void buy_property(int index, int price);
    // interacting with other classes, not implementing for now
    void take_mortgage(int index, int price);
    void pay_off_mortgage(int index, int price);
    void buy_house(int index, int price);
    void buy_hotel(int index, int price);

    // miscellaneous
    void player_description();
};

class Human : public Player {
private:
    bool pass_login;
    std::string password;
public:
    Human(std::string name_input, std::string set_pass="");
    void set_password(std::string new_p);
    void change_password(std::string old_p, std::string new_p);
    void remove_password(std::string pass);
};

class Bot : public Player {
public:
    Bot(std::string name_input);
    void change_name(std::string name_input);
};