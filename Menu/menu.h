#pragma once
//#include "../Player/player.cpp"
//#include "../Dices/dices.cpp"
#include "../Board/board.cpp"
#include "../Cards/cards.cpp"
#include "../Player/player_driver.cpp"
#include <vector>

class Order{
    public:
    Order();
    Order(std::vector<Player> players, Hand hand, Board board, Deck<Card> chance, Deck<Card> chest);
    void add_players(std::vector<Player> players, Hand hand, Board board, Deck<Card> chance, Deck<Card> chest);
    void shuffle();
    PlayerDriver whose_turn();
    void print_order();
    std::vector<PlayerDriver> players_order;
    std::vector<Player> players_list;
};

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
    std::vector<Dice> dices;
    Order order;
    Hand hand;
    Deck<Card> chest; //chest
    Deck<Card> chance;
    Board board;
};