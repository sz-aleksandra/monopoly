// Project: Monopoly
// Author: Jakub Bąba

#include <iostream>
#include "player.h"

int main() {
    if (DEBUG)
        std::cout << "DEBUG MODE\n\n";
    Human p1("Jakub");
    Bot p2("Mark");
    p1.add_money(50);
    p1.player_description();
    p2.player_description();
    return 0;
}
