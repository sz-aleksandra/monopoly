// Project: Monopoly
// Author: Jakub Bąba

#include "player.h"

Player::Player(std::string name_input) {
    name = std::move(name_input);
    money = 1500;
    position = 0;
    in_jail = false;
    alive = true;
}

/* ---------- SETTERS ---------- */
void Player::change_name(std::string name_input) {
    if (!name_input.empty())
        name = std::move(name_input);
    else if (DEBUG)
        std::cout << "Name cannot be empty\n";
}

void Player::add_money(int amount) {
    money += amount;
}

void Player::take_money(int amount) {
    if (amount <= money)
        money -= amount;
    else {
        if (DEBUG)
            std::cout << "Tried to remove more money than player has\n";
        // interaction to start selling Player stuff to be implemented
    }
}

void Player::move_player(int amount) {
    // assuming that size is 40
    while (position + amount < 0)
        position += 40;
    position = (position + amount) % 40;
}

void Player::set_position(int new_location) {
    if (new_location < 40 && new_location >= 0)
        position = new_location;
    else if (DEBUG)
        std::cout << "Tried to move outside board\n";
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


/* ---------- GETTERS ---------- */
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
    std::cout << "Player name: " << name;
    std::cout << "\nMoney amount: " << money;
    std::cout << "\nPosition on board (index): " << position;
    std::cout << "\nIs alive: " << ( (alive) ? "Yes" : "No" );
    std::cout << "\nIs in jail: " << ( (in_jail) ? "Yes" : "No" );
    std::cout << "\nOwned properties (indexes): ";
    for (auto i : properties)
        std::cout << i << " ";
    std::cout << "\n\n";
}