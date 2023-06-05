// Project: Monopoly
// Author: Jakub Bąba

#pragma once
#include <iostream>

class not_enough_money_exception : public std::exception {
private:
    char *message;
public:
    not_enough_money_exception(char *msg) : message(msg) {}
    char *what() {
        return message;
    }
};

class empty_name_exception : public std::exception {
private:
    char *message;
public:
    empty_name_exception(char *msg) : message(msg) {}
    char *what() {
        return message;
    }
};

class invalid_player_type_exception : public std::exception {
private:
    char *message;
public:
    invalid_player_type_exception(char *msg) : message(msg) {}
    char *what() {
        return message;
    }
};

class position_outside_board_exception : public std::exception {
private:
    char *message;
public:
    position_outside_board_exception(char *msg) : message(msg) {}
    char *what() {
        return message;
    }
};

class invalid_field_type_exception : public std::exception {
private:
    char *message;
public:
    invalid_field_type_exception(char *msg) : message(msg) {}
    char *what() {
        return message;
    }
};