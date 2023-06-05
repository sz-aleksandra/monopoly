#include <string>
#include <vector>
#include <memory>

#pragma once

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
    Deck<CardType>();
    Deck<CardType>(std::vector<std::shared_ptr<CardType>> cards);
    void add_cards(std::vector<std::shared_ptr<CardType>> cards);
    void shuffle();
    std::shared_ptr<CardType> draw_card();
    std::vector<std::shared_ptr<CardType>> load_cards_from_file(std::string file);
    void save_deck(std::string file);
    void print_deck();
    std::vector<std::shared_ptr<CardType>> deck;
};