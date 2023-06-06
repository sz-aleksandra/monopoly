#pragma once
#include <vector>
#include <random>
#include <iostream>

class Dice{
    public:
    Dice(int max_result);
    int roll();
    int sides;
};

class Hand{
    public:
    Hand();
    Hand(std::vector<Dice> dices);
    void add_dices(std::vector<Dice> dices);
    int roll_all(bool print=false);
    std::vector<Dice> dice_collection;
    int same_result_counter;
};