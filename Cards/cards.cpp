#pragma once
#include "cards.h"

Card::Card(std::string text, int number){
    message = text;
    amount = number;
}

PayCard::PayCard(std::string text, int number): Card(text, number){
    message = text;
    amount = number;
}

void PayCard::effect(std::string player_name, std::string optional_receiver){
    std::cout << message << std::endl;
    if (amount <= 100){ // 100 is hypothetical players amount of money
        std::cout << "Player " << player_name << " pays " << amount << "$ to " << optional_receiver << std::endl;
    } else { //before this there would be option to sell one of propterites, but there is no way of checking it wihout player class
        std::cout << "Player" << player_name << " goes to jail";
    }
}

GetMoneyCard::GetMoneyCard(std::string text, int number) : Card(text, number){
    message = text;
    amount = number;
}

void GetMoneyCard::effect(std::string player_name, std::string optional_receiver){
    std::cout << message << std::endl;
    std::cout << "Player " << player_name << " receives " << amount << "$" << std::endl;
}

GetOutOfJailCard::GetOutOfJailCard(std::string text, int number) : Card(text, number){
    message = text;
    amount = number;
}

void GetOutOfJailCard::effect(std::string player_name, std::string optional_receiver){
    std::cout << message << std::endl;
    std::cout << "Player " << player_name << " receives GetOutOfJailCard" << std::endl;
}

MoveCard::MoveCard(std::string text, int number) : Card(text, number){
    message = text;
    amount = number;
}

void MoveCard::effect(std::string player_name, std::string optional_receiver){
    std::cout << message << std::endl;
    if (amount != 11){
        std::cout << "Player " << player_name << " moves to location " << amount << "." << std::endl;
    } else {
        std::cout << "Player " << player_name << " moves to jail."<< std::endl;
    }
}
