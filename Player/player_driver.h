// Project: Monopoly
// Author: Jakub Bąba

#pragma once
#include <iostream>
#include <cctype>
#include <algorithm>
#include "player.h"
#include "dices.h"
#include "consoleview.h"
#include "board.h"
#include "cards.h"

class PlayerDriver {
private:
    Player &player;
    Hand &hand;
    Board board;
    Deck<Card> deck_chance;
    Deck<Card> deck_chest;
    vector<Player> all_players;
    int go_out_chances;
public:
    PlayerDriver(Player &unit, Hand &roller, Board &board, Deck<Card> &chances, Deck<Card> &chests, vector<Player> &players);
    void make_turn();
    void move();
    void new_position_actions();
    void buy_house_menu();

    void property_actions();
    void utility_actions();
    void railroads_actions();
    void penalty_actions();
    void card_actions(std::string type);
    void go_jail_actions();

    void change_position_actions(std::string type, int value, bool skip_start=false); // types are move and set
    void give_money_actions(int amount);
    void take_money_actions(int amount);
    void put_in_jail_actions();
    void put_out_of_jail_actions();

    void buy_house();
    void buy_property(int index, int price);
    void pay_to_other(PlayerDriver &receiver, int amount);
};
