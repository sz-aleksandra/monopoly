#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>

class Card{
    public:
    Card(std::string text, int number);
    virtual void effect(std::string player_name="", std::string optional_receiver="the bank") = 0;  //abstract method, will have player as an argument, but now its independent
    std::string message;
    int amount;
};

class PayCard : public Card{
    public:
    PayCard(std::string text, int number=0);
    virtual void effect(std::string player_name="", std::string optional_receiver="the bank") override;  //abstract method, will have player as an argument, but now its independent
    std::string message;
    int amount;
};

class GetMoneyCard : public Card{
    public:
    GetMoneyCard(std::string text, int number=0);
    virtual void effect(std::string player_name="", std::string optional_receiver="the bank") override;  //abstract method, will have player as an argument, but now its independent
    std::string message;
    int amount;
};

class GetOutOfJailCard : public Card{
    public:
    GetOutOfJailCard(std::string text, int number=0);
    virtual void effect(std::string player_name="", std::string optional_receiver="the bank") override;  //abstract method, will have player as an argument, but now its independent
    std::string message;
    int amount;
};

class MoveCard : public Card{
    public:
    MoveCard(std::string text, int number=0);
    virtual void effect(std::string player_name="", std::string optional_receiver="the bank") override;  //abstract method, will have player as an argument, but now its independent
    std::string message;
    int amount;
};

template <class CardType> //chance or community cards
class Deck{
    public:
    Deck<CardType>() {};
    Deck<CardType>(std::vector<std::shared_ptr<CardType>> cards) {
        deck = cards;
    };
    void add_cards(std::vector<std::shared_ptr<CardType>> cards) {
        for (int card_pos=0; card_pos < cards.size(); ++card_pos){
            deck.push_back(cards[card_pos]);
        }
    };
    void shuffle() {
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine{});
    };
    std::shared_ptr<CardType> draw_card() {
        std::rotate(deck.begin(), deck.begin() + 1, deck.end());
        return deck[deck.size() - 1];
    };
    std::vector<std::shared_ptr<CardType>> load_cards_from_file(std::string file) {
        std::vector<std::shared_ptr<CardType>> card_collection;
        std::string line;
        std::ifstream input_file;
        int amount_as_int;
        input_file.open(file);
        if (input_file){
            while(std::getline(input_file, line)){
                std::string type;
                std::string text;
                std::string amount;
                bool readintotext = 0;
                bool readamount = 0;
                char c = line[0];
                for (char c : line){
                    if (c == ','){
                        readintotext = 1;
                        continue;
                    } else if (c == ';'){
                        readamount = 1;
                        continue;
                    }
                    if (readamount){
                        amount += c;
                    } else if (readintotext){
                        text += c;
                    } else {
                        type += c;
                    }
                }
                if(type == "7PayCard"){
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
                    card_collection.push_back(std::make_shared<MoveCard>(text, std::stoi(amount)));
                }
            }
            input_file.close();
        } else {
            std::cout << "Unable to open file";
        }
        return card_collection;
    };
    void save_deck(std::string file) {
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
    };
    void print_deck() {
        for (const auto& card : deck) {
            card->effect();
        }
    };
    std::vector<std::shared_ptr<CardType>> deck;
};