// Project: Monopoly
// Author: Jakub Bąba

#ifndef DEBUG
#   define DEBUG false
#endif
#include "player_driver.h"

// @TODO check if unit is player type
PlayerDriver::PlayerDriver(Player &unit, Hand &roller) : player(unit), hand(roller), go_out_chances(0) {}

void PlayerDriver::make_turn() {
    // @TODO think about better way to do that, maybe with try
    // it ain't the best looking way, but clion can't work with system calls :c
    for (int i=0; i<100; i++)
        std::cout << "\n";
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
        std::string decision;
        std::cout << "YOU ARE IN JAIL. Choose an action:\n";
        std::cout << "1. Try to roll dices to get out\n";
        if (player.get_money() >= 50)
            std::cout << "2. Pay 50$ fine now\n";
        if (player.get_out_of_jail_cards())
            std::cout << "3. Use go out of jail card (you have " << player.get_out_of_jail_cards() << ") \n";
        std::cout << "Your action: ";
        std::cin >> decision;
        if (decision == "1") {
            std::cout << "You try your luck, rolling dices...\n";
            hand.roll_all(true);
            if (hand.same_result_counter) {
                std::cout << "You got double, you go out of jail\n";
                player.put_out_of_jail();
            }
            else {
                go_out_chances--;
                if (go_out_chances)
                    std::cout << "There is no double, you have " << go_out_chances << " chance" << ((go_out_chances == 1) ? " left.\n" : "s left.\n");
                else {
                    std::cout << "You used all your chances. You have to pay 50$.\n";
                    take_money_actions(50);
                    std::cout << "You paid 50$ and you go out of jail. You have " << player.get_money() << "$.\n";
                    player.put_out_of_jail();
                }
            }
        }
        else if (decision == "2" && player.get_money() >= 50) {
            player.take_money(50);
            player.put_out_of_jail();
            std::cout << "You paid 50$. You have " << player.get_money() << "$.\n";
        }
        else if (decision == "3" && player.get_out_of_jail_cards()) {
            player.take_out_of_jail_card();
            player.put_out_of_jail();
            std::cout << "You used out of jail card. You have " << player.get_out_of_jail_cards() << " card" << ((player.get_out_of_jail_cards() == 1) ? ".\n" : "s.\n");
        }
        else {
            std::cout << "Invalid option!\n\n";
            move();
        }

    }
    else {  // just normal move
        std::cout << "Rolling dices...\n";
        int roll_total = hand.roll_all(true);
        if (hand.same_result_counter >= 3) {
            std::cout << "THREE DOUBLES: YOU GO TO JAIL\n";
            hand.same_result_counter = 0;
            put_in_jail_actions();
        }
        else if (hand.same_result_counter) {
            std::cout << "DOUBLE, you will have next move after this one\n";
            change_position_actions("move", roll_total);
            move();
        }
        else
            change_position_actions("move", roll_total);
    }
    std::cout << "End of move. Press any key to continue...";
    std::cin.get();
    std::cin.get();     // sometimes will lag but anyway
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

void PlayerDriver::put_in_jail_actions() {
    player.put_in_jail();
    player.set_position(10);
    go_out_chances = 3;
}