#include "menu.h"
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

void clear_screen(){
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

Menu::Menu(){

}

void Menu::print_menu_screen(){
    std::string option;
    std::string options = R"(
                                                         press S to START Game
                                                         press P to add PLAYERS
                                                         press D to add DICES
                                                         press E to EXIT
    )";
    while (true){
        clear_screen();
        std::cout << TITLE << std::endl;
        std::cout << options << std::endl;
        std::cin >> option;
        switch (option[0]){
            case 'S':
                //make turn?
                break;
            case 's':
                //make turn?
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
            case 'E':
                std::cout << R"(
                                                              Exiting...
                )";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                clear_screen();
                std::exit(0);
                break;
            case 'e':
                std::cout << R"(
                                                              Exiting...
                )";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                clear_screen();
                std::exit(0);
                break;
            default:
                std::cout << R"(
                                                       Invalid option! Try again.
                )";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
        }
    }
}

void Menu::add_players(){
    std::string input;
    clear_screen();
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
                                                            Invalid argument!
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
    clear_screen();
    std::string options = R"(
                                            Enter nicknames for your players then press ENTER. When you finish press "."
    )";
    std::cout << TITLE << std::endl;
    std::cout << options << std::endl;
    std::cin >> input;
    while ((input != ".") || (players.size() == 0)){
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
        clear_screen();
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
    clear_screen();
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
        clear_screen();
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

Order::Order(std::vector<Player> players){
    players_order = players;
}

void Order::shuffle(){
    std::shuffle(players_order.begin(), players_order.end(), std::default_random_engine{});
}

Player Order::whose_turn(){
    std::rotate(players_order.begin(), players_order.begin() + 1, players_order.end());
    return players_order[players_order.size() - 1];
}

void Order::print_order(){
    std::cout << "Turn: " << players_order[players_order.size() - 1].get_name() << std::endl;
    std::cout << "Next:" << std::endl;
    for (int i = 0; i < players_order.size() - 1; ++i){
        std::cout << i + 1 << ". " << players_order[i].get_name() << std::endl;
    }
}