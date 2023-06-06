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

    // @TODO implement houses mechanics
//    std::cout << "Do you want to buy houses? (Yes/No): ";
//    std::string decision;
//    std::cin >> decision;
//    transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
//    if (decision == "yes" || decision == "y") {
//        buy_house_menu();
//    }

    move();
}

void PlayerDriver::move() {
    if (player.is_in_jail()) {
        // @TODO implement what happens when in jail
    }
    else {  // just normal move
        std::cout << "Rolling dices...\n";
        int roll_total = hand.roll_all(true);
        if (hand.same_result_counter >= 3) {
            std::cout << "THREE DOUBLES: YOU GO TO JAIL\n";
            hand.same_result_counter = 0;
            go_jail_actions();
        }
        else if (hand.same_result_counter) {
            std::cout << "DOUBLE, you will have next move after this one\n";
            change_position_actions("move", roll_total);
            move();
        }
        else
            change_position_actions("move", roll_total);
    }
}

void PlayerDriver::new_position_actions() {
    std::string type;
    // @TODO get field type from board (?) class and update types names
    type = "property";
    if (type == "property")
        property_actions();
    else if (type == "utility")
        utility_actions();
    else if (type == "station")
        station_actions();
    else if (type == "tax")
        tax_actions();
    else if (type == "chance" || type == "community")
        card_actions(type);
    else if (type == "wait")
        ;
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

void PlayerDriver::property_actions() {}

void PlayerDriver::utility_actions() {}

void PlayerDriver::station_actions() {}

void PlayerDriver::tax_actions() {}

void PlayerDriver::card_actions(std::string type) {}

void PlayerDriver::go_jail_actions() {}

void PlayerDriver::change_position_actions(std::string type, int value, bool skip_start) {
    if (type == "move") {
        if (!skip_start && player.get_position() + value >= 40)
            give_money_actions(200);
        player.move_player(value);
    }
    else if (type == "set") {
        if (!skip_start && player.get_position() < value)
            give_money_actions(200);
        player.set_position(value);
    }
    else {
        std::cout << "This type of change position action does not exist";
        std::cout << "\nReceived type: " << type << "\n\n";
        throw invalid_action_type_exception("Non existent type of position change action");
    }
    new_position_actions();
}

void PlayerDriver::give_money_actions(int amount) {
    player.add_money(amount);
}

void PlayerDriver::take_money_actions(int amount) {
    try {
        player.take_money(amount);
    }
    catch (not_enough_money_exception& e) {
        // @TODO bankruptcy mechanics
    }
}
