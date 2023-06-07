#pragma once
#include "menu.h"
//#include "../ConsoleView/consoleview.cpp"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <algorithm>

std::string TITLE = R"(
    MMM         MMM      OOOOOO      NNN         NNN      OOOOOO      PPPPPPPPP         OOOOOO      LLL            YYY         YYY
    MMMMMM   MMMMMM   OOO      OOO   NNNNNN      NNN   OOO      OOO   PPP      PPP   OOO      OOO   LLL            YYY         YYY
    MMM   MMM   MMM   OOO      OOO   NNN   NNN   NNN   OOO      OOO   PPP      PPP   OOO      OOO   LLL               YYY   YYY
    MMM         MMM   OOO      OOO   NNN      NNNNNN   OOO      OOO   PPPPPPPPP      OOO      OOO   LLL                  YYY
    MMM         MMM   OOO      OOO   NNN         NNN   OOO      OOO   PPP            OOO      OOO   LLLLLLLLLLLL         YYY
    MMM         MMM      OOOOOO      NNN         NNN      OOOOOO      PPP               OOOOOO      LLLLLLLLLLLL         YYY
    )";

void clear(){
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

Menu::Menu(){
    board = Board("../Board/plansza1.txt");
    turn = 0;
    max_turn = 50;
}

void Menu::print_menu_screen(){
    chest.add_cards(chest.load_cards_from_file("../Cards/deck.txt"));

    chance.add_cards(chance.load_cards_from_file("../Cards/deck.txt"));

    board.setNumberOfPlayers(players.size());

    std::string option;
    std::string options = R"(
                                                                press S to START Game
                                                                press P to add PLAYERS
                                                                press D to add DICES
                                                                press O to change OPTIONS
                                                                press E to EXIT
    )";
    while (true){
        clear();
        std::cout << TITLE << std::endl;
        std::cout << options << std::endl;
        std::cin >> option;
        switch (option[0]){
            case 'S':
                if ((dices.size() != 0) && (players.size() != 0)){
                    hand = Hand();
                    hand.add_dices(dices);
                    for (auto& dice : hand.dice_collection){
                        std::cout << dice.sides << "; ";
                    }
                    order = Order();
                    order.add_players(players, hand, board, chance, chest);

                    while ((how_many_players_left() > 1) && (turn != max_turn)){
                        //std::cout << turn << std:: endl;
                        order.whose_turn().make_turn();
                        turn += 1;
                    }
                    clear();
                    std::cout << "And the winner is: ";
                    for (auto& player : get_winner()){
                        std::cout << player.get_name() << "! ";
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                    std::cout << std::endl;
                } else {
                    std::cout << R"(
                                                        You need to add dices and players first!
                )" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                clear();
                }
                break;
            case 's':
                if ((dices.size() != 0) && (players.size() != 0)){
                    hand = Hand();
                    hand.add_dices(dices);
                    for (auto& dice : hand.dice_collection){
                        std::cout << dice.sides << "; ";
                    }
                    order = Order();
                    order.add_players(players, hand, board, chance, chest);

                    while (how_many_players_left() > 1){
                        order.whose_turn().make_turn();
                    }
                } else {
                    std::cout << R"(
                                                        You need to add dices and players first!
                )" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                clear();
                }
                break;
            case 'P':
                add_players();
                break;
            case 'p':
                add_players();
                break;
            case 'D':
                add_dices();
                break;
            case 'd':
                add_dices();
                break;
            case 'O':
                get_max_turns();
                break;
            case 'o':
                get_max_turns();
                break;
            case 'E':
                std::cout << R"(
                                                                    Exiting...
                )" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                clear();
                std::exit(0);
                break;
            case 'e':
                std::cout << R"(
                                                                    Exiting...
                )" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                clear();
                std::exit(0);
                break;
            default:
                std::cout << R"(
                                                            Invalid option! Try again.
                )" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
        }
    }
}

void Menu::add_players(){
    std::string input;
    clear();
    std::string options = R"(
                                                                press P to add PLAYERS
                                                                press B to add BOTS
    )";
    std::cout << TITLE << std::endl;
    std::cout << options << std::endl;
    std::cin >> input;
    switch (input[0]){
        case 'P':
            get_nicknames(0);
            break;
        case 'p':
            get_nicknames(0);
            break;
        case 'B':
            get_nicknames(1);
            break;
        case 'b':
            get_nicknames(1);
            break;
        default:
            std::cout << R"(
                                                                Invalid argument! Try again.
            )" << std::endl;
            break;
    }
    std::cout << "Players in use: ";
    for (auto& player : players){
        std::cout << player.get_name() << "; ";
    }
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Menu::get_nicknames(bool bot){
    std::string input;
    clear();
    std::string options = R"(
                                            Enter nicknames for your players (up to 8) then press ENTER. When you finish press "."
    )";
    std::cout << TITLE << std::endl;
    std::cout << options << std::endl;
    std::cin >> input;
    while (((input != ".") || (players.size() == 0)) && (players.size() != 6)){
        if ((input == "") || (input == "") || (input == " ") || (input == "\t") || (check_if_used(input))){
            std::cout << R"(
                                                        Invalid argument! Nickname has already been used.
            )" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        } else {
            nicknames.push_back(input);
            if (bot){
                players.push_back(Player(input, "bot"));
            } else {
                players.push_back(Player(input));
            }
        }
        clear();
        std::cout << TITLE << std::endl;
        std::cout << options << std::endl;
        std::cin >> input;
    }
}

bool Menu::check_if_used(std::string nickname){
    for (auto& nick : nicknames){
        if (nick == nickname){
            return 1;
        }
    }
    return 0;
}

void Menu::add_dices(){
    bool correct;
    std::string input;
    clear();
    std::string options = R"(
                                            Enter number of sides for your dices then press ENTER. When you finish press "."
    )";
    std::cout << TITLE << std::endl;
    std::cout << options << std::endl;
    std::cin >> input;
    while ((input != ".") || (dices.size() == 0)){
        correct = 1;
        for (char character : input){
            if (!std::isdigit(character)){
                correct = 0;
            }
        }
        if (correct){
            dices.push_back(Dice(std::stoi(input)));
        } else {
            std::cout << R"(
                                                            Invalid argument! Enter an integer.
            )" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
        clear();
        std::cout << TITLE << std::endl;
        std::cout << options << std::endl;
        std::cin >> input;
    }
    std::cout << "Dices in use: ";
    for (auto& dice : dices){
        std::cout << dice.sides << "; ";
    }
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Menu::get_max_turns(){
    std::string input;
    clear();
    std::string options = R"(
                                            Enter max number of turns to finish game after and then press ENTER
    )";
    std::cout << TITLE << std::endl;
    std::cout << options << std::endl;
    std::cin >> input;
    bool correct = 1;
    for (char character : input){
        if (!std::isdigit(character)){
            correct = 0;
        }
    }
    if ((correct) && (std::stoi(input) > 0)){
        max_turn = std::stoi(input);
    } else {
        std::cout << R"(
                                                        Invalid argument! Enter an integer.
        )" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        clear();
        std::cout << TITLE << std::endl;
        std::cout << options << std::endl;
        std::cin >> input;
    }
    std::cout << "Max number of turns: " << input << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int Menu::how_many_players_left(){
    int how_many = 0;
    for (auto& player : players){
        if (player.is_alive()){
            how_many += 1;
        }
    }
    return how_many;
}

std::vector<Player> Menu::get_winner(){
    int most_money = 0;
    //Player current_winner("ඞ");
    std::vector<Player> current_winners;
    if (how_many_players_left() > 1) {
        for (auto& player : players){
            if (player.is_alive()){
                if (player.get_money() > most_money){
                    current_winners = {player};
                } else if (player.get_money() == most_money){
                    current_winners.push_back(player);
                }
            }
        }
    } //else {
        //for (auto& player : players){
            //if (player.is_alive()){
                //current_winners = {player};
            //}
        //}
    //}
    return current_winners;
}

Order::Order(){

}

Order::Order(std::vector<Player> &players, Hand &hand, Board &board, Deck<Card> &chance, Deck<Card> &chest){
    for (auto& player : players){
        players_order.push_back(PlayerDriver(&player, &hand, &board, &chance, &chest, &players));
    }
}

void Order::add_players(std::vector<Player> &players, Hand &hand, Board &board, Deck<Card> &chance, Deck<Card> &chest){
    for (auto& player : players){
        players_order.push_back(PlayerDriver(&player, &hand, &board, &chance, &chest, &players));
    }
}

void Order::shuffle(){
    std::shuffle(players_order.begin(), players_order.end(), std::default_random_engine{});
}

PlayerDriver Order::whose_turn(){
    std::rotate(players_order.begin(), players_order.begin() + 1, players_order.end());
    return players_order[players_order.size() - 1];
}

void Order::print_order(){
    std::cout << "Turn: " << players_order[players_order.size() - 1].player->get_name() << std::endl;
    std::cout << "Next:" << std::endl;
    for (int i = 0; i < players_order.size() - 1; ++i){
        std::cout << i + 1 << ". " << players_order[i].player->get_name() << std::endl;
    }
}