#include <vector>

#pragma once

class Dice{
    public:
    Dice(int max_result);
    int roll();
    int sides;
};

class Hand{
    public:
    Hand(std::vector<Dice> dices);
    int roll_all();
    std::vector<Dice> dice_collection;
    int same_result_counter;
};