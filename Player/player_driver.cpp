// Project: Monopoly
// Author: Jakub Bąba

#ifndef DEBUG
#   define DEBUG false
#endif
#include "player_driver.h"

// @TODO check if unit is player type
PlayerDriver::PlayerDriver(Player &unit, Hand &roller, Board &board) : player(unit), hand(roller), board(board), go_out_chances(0) {}

void PlayerDriver::make_turn() {
    // @TODO think about better way to do that, maybe with try
    clear_screen();
    board.printBoard();
    std::cout << "\n------------------------------\n";
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

    std::cout << "End of move. Press ENTER to continue...";
    wait_for_key();
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
                put_out_of_jail_actions();
            }
            else {
                go_out_chances--;
                if (go_out_chances)
                    std::cout << "There is no double, you have " << go_out_chances << " chance" << ((go_out_chances == 1) ? " left.\n" : "s left.\n");
                else {
                    std::cout << "You used all your chances. You have to pay 50$.\n";
                    take_money_actions(50);
                    std::cout << "You paid 50$ and you go out of jail. You have " << player.get_money() << "$.\n";
                    put_out_of_jail_actions();
                }
            }
        }
        else if (decision == "2" && player.get_money() >= 50) {
            player.take_money(50);
            put_out_of_jail_actions();
            std::cout << "You paid 50$. You have " << player.get_money() << "$.\n";
        }
        else if (decision == "3" && player.get_out_of_jail_cards()) {
            player.take_out_of_jail_card();
            put_out_of_jail_actions();
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
}

void PlayerDriver::new_position_actions() {
    board.movePlayer(player.get_id(), player.get_position());
    board.printBoard();
    std::string name = board.get_field(player.get_position())->getName();
    std::cout << "You are on " << name << "\n";
    std::string type = board.get_field(player.get_position())->getType();
    if (type == "property")
        property_actions();
    else if (type == "utility")
        utility_actions();
    else if (type == "railroads")
        railroads_actions();
    else if (type == "penalty")
        penalty_actions();
    else if (type == "chance" || type == "chest")
        card_actions(type);
    else if (type == "special" && name == "Go_To_Jail")
        go_jail_actions();
    else if (type == "special")
        ;
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

void PlayerDriver::property_actions() {
    auto field = (Property*)board.get_field(player.get_position());
    std::string name = field->getName();
    int owner = field->getOwner();
    if (!owner) {
        int cost = field->getPurchasePrice();
        std::string decision;
        std::cout << "No one has bought " << name << " yet. Cost of the field: " << cost << "$.\n";
        std::cout << "Do you want to buy it? Yes/No: ";
        std::cin >> decision;
        transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
        if (decision == "yes" || decision == "y") {
            buy_property(player.get_position(), cost);
            std::cout << "You bought " << name << ". Now you have " << player.get_money() << "$.\n";
        }
    }
    else if (owner == player.get_id()) {
        std::cout << name << " is your property. Now you're chilling around flags with your face.\n";
    }
    else {
        int rent = 0; // @TODO finish when implemented
        std::cout << "Unfortunately, someone was here before you. Now you gotta pay " << rent << " $.\n";
        // @TODO think about way to access other player
    }

}

void PlayerDriver::utility_actions() {
    auto field = (Utility*)board.get_field(player.get_position());
    std::string name = field->getName();
    int owner = field->getOwner();
    if (!owner) {
        int cost = field->getPurchasePrice();
        std::string decision;
        std::cout << "No one has bought " << name << " yet. Cost of the field: " << cost << "$.\n";
        std::cout << "Do you want to buy it? Yes/No: ";
        std::cin >> decision;
        transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
        if (decision == "yes" || decision == "y") {
            buy_property(player.get_position(), cost);
            std::cout << "You bought " << name << ". Now you have " << player.get_money() << "$.\n";
        }
    }
    else if (owner == player.get_id()) {
        std::cout << name << " is your utility. Now you're chilling while seeing your workers.\n";
    }
    else {
        int multiplier = 0; // @TODO finish when implemented
        std::cout << "Unfortunately, someone was here before you. Now roll will decide about your fate. Rolling dices...\n\n";
        int pay_base = hand.roll_all();
        std::cout << "Multiplier is " << multiplier << ", and roll result is " << pay_base << ". So you are paying " << multiplier*pay_base << "$.\n";
        // @TODO think about way to access other player
    }
}

void PlayerDriver::railroads_actions() {
    auto field = (RailRoads*)board.get_field(player.get_position());
    std::string name = field->getName();
    int owner = field->getOwner();
    if (!owner) {
        int cost = field->getPurchasePrice();
        std::string decision;
        std::cout << "No one has bought " << name << " yet. Cost of the field: " << cost << "$.\n";
        std::cout << "Do you want to buy it? Yes/No: ";
        std::cin >> decision;
        transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
        if (decision == "yes" || decision == "y") {
            buy_property(player.get_position(), cost);
            std::cout << "You bought " << name << ". Now you have " << player.get_money() << "$.\n";
        }
    }
    else if (owner == player.get_id()) {
        std::cout << name << " is your railroad. You got a free tour around area, cool!\n";
    }
    else {
        int rent = 0; // @TODO finish when implemented
        std::cout << "Unfortunately, someone was here before you. Now you gotta pay " << rent << " $.\n";
        // @TODO think about way to access other player
    }
}

void PlayerDriver::penalty_actions() {
    auto field = (Penalty*)board.get_field(player.get_position());
    int to_pay = field->getTaxToPay();
    std::cout << "You know what time is it? Time for tax! You pay " << to_pay << "$.\n";
    take_money_actions(to_pay);
    std::cout << "Now you have " << player.get_money() << "$.\n";
}

void PlayerDriver::card_actions(std::string type) {
    //@TODO
}

void PlayerDriver::go_jail_actions() {
    std::cout << "You landed on Go To Jail field, you know what happens next...\n";
    put_in_jail_actions();
}

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
    board.movePlayer(player.get_id(), player.get_position());
    go_out_chances = 3;
}

void PlayerDriver::put_out_of_jail_actions() {
    player.put_out_of_jail();
    player.set_position(10);
    board.movePlayer(player.get_id(), player.get_position());
}

void PlayerDriver::buy_property(int index, int price) {
    take_money_actions(price);
    player.add_property(index);
}

void PlayerDriver::pay_to_other(PlayerDriver &receiver, int amount) {
    take_money_actions(amount);
    receiver.give_money_actions(amount);
}