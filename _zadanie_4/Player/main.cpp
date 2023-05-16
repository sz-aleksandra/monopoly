// Project: Monopoly
// Author: Jakub Bąba

#include <iostream>
#include "player.h"

int main() {
    if (DEBUG)
        std::cout << "DEBUG MODE\n\n";
    Player p1 = Player("Jakub");
    p1.player_description();
    return 0;
}
