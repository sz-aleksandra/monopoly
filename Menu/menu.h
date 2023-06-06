#include "../Player/player.cpp"
#include "../Dices/dices.cpp"
#include <vector>

#pragma once

class Menu{
    public:
    Menu();
    void print_menu_screen();
    void add_players();
    void get_nicknames(bool bot);
    bool check_if_used(std::string nickname);
    void add_dices();
    void start_game();
    std::vector<Player> players;
    std::vector<std::string> nicknames;
    std::vector<Player> bots;
    std::vector<Dice> dices;
};

class Order{
    public:
    Order(std::vector<Player> players);
    void shuffle();
    Player whose_turn();
    void print_order();
    std::vector<Player> players_order;
};