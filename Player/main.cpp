// Project: Monopoly
// Author: Jakub Bąba

#ifndef DEBUG
#   define DEBUG false
#endif
#include <iostream>
#include <vector>
#include "player.h"
#include "player_driver.h"
#include "../Dices/dices.h"

int main() {
    if (DEBUG)
        std::cout << "DEBUG MODE\n\n";
    Player p1("Jakub");
    Player p2("Mark", "bot");
    p2.add_money(50);
    p1.player_description();
    p2.player_description();

    std::vector<Dice> my_dices;
    my_dices.emplace_back(6);
    my_dices.emplace_back(6);
    Hand h(my_dices);
    PlayerDriver driver1(p1, h);
    driver1.make_turn();

    return 0;
}
