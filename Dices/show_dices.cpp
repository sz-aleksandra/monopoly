//program showcasing dices and ahnd classes

#include "dices.cpp"
#include <iostream>

int main(){
    std::vector<Dice> my_dices;
    my_dices.push_back(Dice(3));
    my_dices.push_back(Dice(3));
    Hand hand(my_dices);
    std::cout << hand.roll_all() << std::endl;
    std::cout << "same_results:" << hand.same_result_counter << std::endl;
    return 0;
}