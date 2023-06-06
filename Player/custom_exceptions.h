// Project: Monopoly
// Author: Jakub Bąba

#pragma once
#include <iostream>

class not_enough_money_exception : public std::exception {
private:
    std::string message;
public:
    not_enough_money_exception(std::string msg) : message(std::move(msg)) {}
    const char* what() noexcept {
        return message.c_str();
    }
};

class empty_name_exception : public std::exception {
private:
    std::string message;
public:
    empty_name_exception(std::string msg) : message(std::move(msg)) {}
    const char* what() noexcept {
        return message.c_str();
    }
};

class invalid_player_type_exception : public std::exception {
private:
    std::string message;
public:
    invalid_player_type_exception(std::string msg) : message(std::move(msg)) {}
    const char* what() noexcept {
        return message.c_str();
    }
};

class position_outside_board_exception : public std::exception {
private:
    std::string message;
public:
    position_outside_board_exception(std::string msg) : message(std::move(msg)) {}
    const char* what() noexcept {
        return message.c_str();
    }
};

class invalid_field_type_exception : public std::exception {
private:
    std::string message;
public:
    invalid_field_type_exception(std::string msg) : message(std::move(msg)) {}
    const char* what() noexcept {
        return message.c_str();
    }
};

class invalid_action_type_exception : public std::exception {
private:
    std::string message;
public:
    invalid_action_type_exception(std::string msg) : message(std::move(msg)) {}
    const char* what() noexcept {
        return message.c_str();
    }
};

class no_out_of_jail_cards_exception : public std::exception {
private:
    std::string message;
public:
    no_out_of_jail_cards_exception(std::string msg) : message(std::move(msg)) {}
    const char* what() noexcept {
        return message.c_str();
    }
};