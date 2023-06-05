#include "dices.h"
#include <random>
#include <iostream> //for printing endling

Dice::Dice(int max_result){
    sides = max_result;
}

int Dice::roll(){
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dis(1, sides);
    return dis(gen);
}

Hand::Hand(std::vector<Dice> dices){
    dice_collection = dices;
}

int Hand::roll_all(){
    int sum = 0;
    int singular_result;
    std::vector<int> all_results;
    for (auto& dice : dice_collection) {
        singular_result = dice.roll();
        //std::cout << singular_result << " "; //for testing or it might be useful to see all results
        sum += singular_result;
        all_results.push_back(singular_result);
    }
    //std::cout << std::endl;
    same_result_counter += 1;
    for (int result : all_results){
        if (result != all_results[0]){
            same_result_counter = 0;
        }
    }
    return sum;
}