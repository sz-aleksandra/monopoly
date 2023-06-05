// Project: Monopoly
// Author: Jakub Bąba

#ifndef DEBUG
#   define DEBUG false
#endif
#include <iostream>
#include "player.h"
#include "player_driver.h"

int main() {
    if (DEBUG)
        std::cout << "DEBUG MODE\n\n";
    Player p1("Jakub");
    Player p2("Mark", "bot");
    p2.add_money(50);
    p1.player_description();
    p2.player_description();

    PlayerDriver driver1(p1);
    driver1.make_turn();

    return 0;
}
