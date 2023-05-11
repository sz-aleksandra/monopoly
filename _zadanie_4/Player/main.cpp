// Project: Monopoly
// Author: Jakub Bąba

#include <iostream>
#include "player.h"

#ifdef NDEBUG
    #define DEBUG 0
#else
    #define DEBUG 1
#endif

int main() {
    if (DEBUG)
        std::cout << "DEBUG MODE\n\n";
    Player p1 = Player("Jakub");
    return 0;
}
