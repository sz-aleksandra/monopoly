#include "dices.h"

Dice::Dice(int max_result){
    sides = max_result;
}

int Dice::roll(){
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<> dis(1, sides);
    return dis(gen);
}

Hand::Hand(){

}

Hand::Hand(std::vector<Dice> dices){
    dice_collection = dices;
    same_result_counter = 0;
}

void Hand::add_dices(std::vector<Dice> dices){
    for (auto& dice : dices){
        dice_collection.push_back(dice);
    }
}

int Hand::roll_all(bool print){
    int sum = 0;
    int dice_counter = 0;
    int singular_result;
    std::vector<int> all_results;
    for (auto& dice : dice_collection) {
        singular_result = dice.roll();
        if (print)
            std::cout << "Dice " << ++dice_counter << ": " << singular_result << "\n";
        sum += singular_result;
        all_results.push_back(singular_result);
    }

    std::cout << "\nTotal: " << sum << "\n\n";

    same_result_counter += 1;
    for (int result : all_results){
        if (result != all_results[0]){
            same_result_counter = 0;
        }
    }
    return sum;
}