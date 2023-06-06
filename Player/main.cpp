// Project: Monopoly
// Author: Jakub Bąba

#ifndef DEBUG
#   define DEBUG false
#endif
#include <iostream>
#include <vector>
#include "player.h"
#include "player_driver.h"
#include "dices.h"
#include "board.h"


using namespace std;
int main() {
    if (DEBUG)
        std::cout << "DEBUG MODE\n\n";
    Player p1("Jakub");
    Player p2("Mark", "bot");

    std::string map = "board.txt";
    Board board(map);

    std::vector<Dice> my_dices;
    my_dices.emplace_back(6);
    my_dices.emplace_back(6);
    Hand h(my_dices);

    PlayerDriver driver1(p1, h, board);
    for (int i=0; i<5; i++) {
        driver1.make_turn();
        std::cout << "\nEnd No. " << i << "\n";
    }


    return 0;
}
