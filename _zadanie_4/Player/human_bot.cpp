// Project: Monopoly
// Author: Jakub Bąba

#include "player.h"

Human::Human(std::string name_input, std::string set_pass)
    : Player(std::move(name_input)),
      password(set_pass), pass_login(!(set_pass.empty())) {}

/* ---------- PASSWORD ---------- */
void Human::set_password(std::string new_p) {
    if (!pass_login) {
        pass_login = true;
        password = std::move(new_p);
    }
    else if (DEBUG)
        std::cout << "Logging in with password is already turned on.\n";
}

void Human::change_password(std::string old_p, std::string new_p) {
    if (pass_login && old_p == password) {
        password = std::move(new_p);
    }
    else if (DEBUG) {
        if (!pass_login)
            std::cout << "Logging in with password is turned off.\n";
        else
            std::cout << "Entered password is incorrect.\n";
    }
}

void Human::remove_password(std::string pass) {
    if (pass_login && pass == password) {
        pass_login = false;
        pass = "";
    }
    else if (DEBUG) {
        if (!pass_login)
            std::cout << "Logging in with password is already turned off.\n";
        else
            std::cout << "Entered password is incorrect.\n";
    }

}

Bot::Bot(std::string name_input)
     : Player(std::move(name_input)) {
    name += " (Bot)";
}

void Bot::change_name(std::string name_input) {
    if (!name_input.empty())
        name = name_input + " (Bot)";
    else if (DEBUG)
        std::cout << "Name cannot be empty\n";
}