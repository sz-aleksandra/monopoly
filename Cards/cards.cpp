#include "cards.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>

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
}

void MoveCard::effect(std::string player_name, std::string optional_receiver){
    std::cout << message << std::endl;
    if (amount != 11){
        std::cout << "Player " << player_name << " moves to location " << amount << "." << std::endl;
    } else {
        std::cout << "Player " << player_name << " moves to jail."<< std::endl;
    }
}

template <class CardType>
Deck<CardType>::Deck(){

}

template <class CardType>
Deck<CardType>::Deck(std::vector<std::shared_ptr<CardType>> cards){
    deck = cards;
}

template <class CardType>
void Deck<CardType>::add_cards(std::vector<std::shared_ptr<CardType>> cards){
    for (int card_pos=0; card_pos < cards.size(); ++card_pos){
        deck.push_back(cards[card_pos]);
    }
}

template <class CardType>
void Deck<CardType>::shuffle(){
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine{});
}

template <class CardType>
std::shared_ptr<CardType> Deck<CardType>::draw_card(){
    std::rotate(deck.begin(), deck.begin() + 1, deck.end());
    return deck[deck.size() - 1];
}

template <class CardType>
std::vector<std::shared_ptr<CardType>> Deck<CardType>::load_cards_from_file(std::string file){
    std::vector<std::shared_ptr<CardType>> card_collection;
    std::string line;
    std::ifstream input_file;
    input_file.open(file);
    if (input_file){
        while(std::getline(input_file, line)){
            std::string type;
            std::string text;
            std::string amount = 0;
            bool readintotext = 0;
            bool readamount = 0;
            char c = line[0];
            for (char c : line){
                if (c == ','){
                    readintotext = 1;
                    continue;
                } else if (c == ';'){
                    readamount = 1;
                }
                if (readamount){
                    amount += c;
                } else if (readintotext){
                    text += c;
                } else {
                    type += c;
                }
            }
            std::cout << amount;
            /*if(type == "7PayCard"){
                //std::shared_ptr<CardType> card = std::make_shared<PayCard>(text);
                card_collection.push_back(std::make_shared<PayCard>(text, std::stoi(amount)));
            }
            if (type == "12GetMoneyCard") {
                card_collection.push_back(std::make_shared<GetMoneyCard>(text, std::stoi(amount)));
            }
            if (type == "16GetOutOfJailCard") {
                card_collection.push_back(std::make_shared<GetOutOfJailCard>(text));
            }
            if (type == "8MoveCard") {
                card_collection.push_back(std::make_shared<MoveCard>(text));
            }*/
        }
        input_file.close();
    } else {
        std::cout << "Unable to open file";
    }
    return card_collection;
}

template <class CardType>
void Deck<CardType>::save_deck(std::string file){
    std::ostringstream oss;
    std::string text = "";
    for (const auto& card : deck) {
        oss << typeid(*card).name() << "," << card->message << ";" << card->amount << std::endl;
    }
    text = oss.str();
    std::ofstream output_file;
    output_file.open(file);
    if (output_file){
        output_file << text;
        output_file.close();
    } else {
        std::cout << "Unable to open file";
    }
}

template <class CardType>
void Deck<CardType>::print_deck(){
    for (const auto& card : deck) {
        card->effect();
    }
}