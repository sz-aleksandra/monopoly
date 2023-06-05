// Project: Monopoly
// Author: Jakub Bąba

#ifndef DEBUG
#   define DEBUG false
#endif
#include "player_driver.h"

// @TODO check if unit is player type
PlayerDriver::PlayerDriver(Player &unit, Hand &roller) : player(unit), hand(roller) {}

void PlayerDriver::make_turn() {
    std::cout << "------------------------------\n";
    std::cout << player.get_name() << " move!\n";
    std::cout << "------------------------------\n\n\n";

    std::cout << "Do you want to buy houses? (Yes/No): ";
    // @TODO check if there are any houses you can build
    std::string decision;
    std::cin >> decision;
    transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
    if (decision == "yes" || decision == "y") {
        buy_house_menu();
    }

    move();
}

void PlayerDriver::move() {
    std::cout << "Rolling dices...\n";
    int roll_total = hand.roll_all(true);
    // @TODO implement doubles

    player.move_player(roll_total);

    std::string type;
    // @TODO get field type from board (?) class and update types names
    type = "property";
    if (type == "property")
        property_actions();
    else if (type == "utility")
        utility_actions();
    else if (type == "station")
        station_actions();
    else if (type == "start")
        start_actions();
    else if (type == "tax")
        tax_actions();
    else if (type == "chance" || type == "community")
        card_actions(type);
    else if (type == "wait")
        wait_actions();
    else if (type == "go_jail")
        go_jail_actions();
    else {
        if (DEBUG) {
            std::cout << "This type of field does not exist";
            std::cout << "\nPlayer: " << player.get_name();
            std::cout << "\nNo. of property: " << player.get_position();
            std::cout << "\nReceived type: " << type << "\n\n";
        }
        throw invalid_field_type_exception("Non-existent type of field");
    }
}

// @TODO implement buying houses mechanics
void PlayerDriver::buy_house_menu() {}

void PlayerDriver::property_actions() {}

void PlayerDriver::utility_actions() {}

void PlayerDriver::station_actions() {}

void PlayerDriver::start_actions() {}

void PlayerDriver::tax_actions() {}

void PlayerDriver::card_actions(std::string type) {}

void PlayerDriver::wait_actions() {}

void PlayerDriver::go_jail_actions() {}
