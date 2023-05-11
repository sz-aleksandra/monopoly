// Project: Monopoly
// Author: Jakub Bąba

#include "player.h"

Player::Player(std::string name_input) {
    name = name_input;
    money = 1500;
    position = 0;
    alive = true;
}

/* ---------- CHANGERS ---------- */
void Player::change_name(std::string name_input) {
    name = name_input;
}

void Player::add_money(int amount) {
    money += amount;
}

void Player::take_money(int amount) {
    money -= amount;
}

void Player::move_player(int amount) {
    // assuming that size is 40
    position = (position + amount) % 40;
}

void Player::set_position(int new_location) {
    position = new_location;
}

void Player::add_property(int index) {
    properties.insert(index);
}

void Player::remove_property(int index) {
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


/* ---------- INTERACTIONS ---------- */
void Player::pay_to_other(Player receiver, int amount) {
    take_money(amount);
    receiver.add_money(amount);
}

void Player::buy_property(int index, int price) {
    take_money(price);
    add_property(index);
}