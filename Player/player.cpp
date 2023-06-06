// Project: Monopoly
// Author: Jakub Bąba

#ifndef DEBUG
#   define DEBUG false
#endif
#include "player.h"

Player::Player(std::string name_input, std::string type) {
    if (type=="human" || type=="bot")
        player_type = std::move(type);
    else {
        if (DEBUG)
            std::cout << "Tried to create player who isn't human nor bot\n";
        throw invalid_player_type_exception("Player has to be human or bot");
    }
    if (name_input.empty()) {
        if (DEBUG)
            std::cout << "Tried to initialize player without name\n";
        throw empty_name_exception("Player cannot be initialized with empty name");
    }
    id = object_count++;
    name = std::move(name_input);
    if (player_type == "bot")
        name += " (Bot)";
    money = 1500;
    position = 0;
    in_jail = false;
    alive = true;
}

/* ---------- SETTERS ---------- */
void Player::change_name(std::string name_input) {
    if (name_input.empty()) {
        if (DEBUG)
            std::cout << "Tried to change name to an empty string\n";
        throw empty_name_exception(("Player cannot have its name changed to an empty string"));
    }
    name = std::move(name_input);
    if (player_type == "bot")
        name += " (Bot)";
}

void Player::add_money(int amount) {
    money += amount;
}

void Player::take_money(int amount) {
    if (amount > money) {
        if (DEBUG)
            std::cout << "Tried to remove more money than player has\n";
        throw not_enough_money_exception(("Tried to take more money than player has"));
    }
    money -= amount;
}

void Player::move_player(int amount) {
    // assuming that size is 40
    while (position + amount < 0)
        position += 40;
    position = (position + amount) % 40;
}

void Player::set_position(int new_location) {
    if (new_location < 0 || new_location >= 40) {
        if (DEBUG)
            std::cout << "Tried to move outside board\n";
        throw position_outside_board_exception("Cannot change player position to one outside board");
    }
    position = new_location;
}

void Player::add_property(int index) {
    if (DEBUG && has_property(index))
        std::cout << "Player already has this property\n";
    properties.insert(index);
}

void Player::remove_property(int index) {
    if (DEBUG && !has_property(index))
        std::cout << "Player didn't have this property\n";
    properties.erase(index);
}

void Player::put_in_jail() {
    if (DEBUG && in_jail)
        std::cout << "Player is already in jail\n";
    in_jail = true;
}

void Player::put_out_of_jail() {
    if (DEBUG && !in_jail)
        std::cout << "Player is already out of jail\n";
    in_jail = false;
}

void Player::kill_player() {
    if (DEBUG && !alive)
        std::cout << "Player is already not alive\n";
    alive = false;
}

void Player::set_player_alive() {
    if (DEBUG && alive)
        std::cout << "Player is already alive\n";
    alive = true;
}


/* ---------- GETTERS ---------- */
int Player::get_id() {
    return id;
}

std::string Player::get_name() {
    return name;
}

int Player::get_money() {
    return money;
}

int Player::get_position() {
    return position;
}

bool Player::has_property(int index) {
    return properties.find(index) != properties.end();
}

bool Player::is_in_jail() {
    return in_jail;
}

bool Player::is_alive() {
    return alive;
}

void Player::player_description() {
    std::cout << "Player id: " << id;
    std::cout << "\nPlayer name: " << name;
    std::cout << "\nMoney amount: " << money;
    std::cout << "\nPosition on board (index): " << position;
    std::cout << "\nIs alive: " << ( (alive) ? "Yes" : "No" );
    std::cout << "\nIs in jail: " << ( (in_jail) ? "Yes" : "No" );
    std::cout << "\nOwned properties (indexes): ";
    for (auto i : properties)
        std::cout << i << " ";
    std::cout << "\n\n";
}