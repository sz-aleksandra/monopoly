#include <string>
#include <vector>
#include <memory>

#pragma once

class Card{
    public:
    Card(std::string text);
    virtual void effect(std::string player_name, int amount, std::string optional_receiver="the bank") = 0;  //abstract method, will have player as an argument, but now its independent
    std::string message;
};

class PayCard : public Card{
    public:
    PayCard(std::string text);
    virtual void effect(std::string player_name, int amount, std::string optional_receiver="the bank") override;  //abstract method, will have player as an argument, but now its independent
    std::string message;
};

class GetMoneyCard : public Card{
    public:
    GetMoneyCard(std::string text);
    virtual void effect(std::string player_name, int amount, std::string optional_receiver="the bank") override;  //abstract method, will have player as an argument, but now its independent
    std::string message;
};

class GetOutOfJailCard : public Card{
    public:
    GetOutOfJailCard(std::string text);
    virtual void effect(std::string player_name, int amount, std::string optional_receiver="the bank") override;  //abstract method, will have player as an argument, but now its independent
    std::string message;
};

class MoveCard : public Card{
    public:
    MoveCard(std::string text);
    virtual void effect(std::string player_name, int amount, std::string optional_receiver="the bank") override;  //abstract method, will have player as an argument, but now its independent
    std::string message;
};

template <class CardType> //chance or community cards
class Deck{
    public:
    Deck<CardType>(std::vector<std::shared_ptr<CardType>> cards);
    void add_cards(std::vector<std::shared_ptr<CardType>> cards);
    void shuffle();
    std::shared_ptr<CardType> draw_card();
    std::vector<std::shared_ptr<CardType>> load_cards_from_file(std::string file);
    void save_deck(std::string file);
    std::vector<std::shared_ptr<CardType>> deck;
};