//program showcasing dices and ahnd classes

#include "dices.h"
#include <iostream>

int main(){
    std::vector<Dice> my_dices;
    my_dices.push_back(Dice(3));
    my_dices.push_back(Dice(3));
    Hand hand(my_dices);
    hand.roll_all(true);
    std::cout << "same_results:" << hand.same_result_counter << std::endl;
    return 0;
}