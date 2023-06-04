// Project: Monopoly
// Author: Jakub Bąba

#ifndef DEBUG
#   define DEBUG false
#endif
#include <iostream>
#include "player.h"

int main() {
    if (DEBUG)
        std::cout << "DEBUG MODE\n\n";
    Player p1("Jakub");
    Player p2("Mark", "bot");
    p1.add_money(50);
    p1.player_description();
    p2.player_description();
    return 0;
}
