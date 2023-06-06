#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    string map_choice = "plansza1.txt";

    Board plansza1(map_choice);
    BoardDisplay board(plansza1);
    board.printBoard(plansza1);
    
    int new_position = 30;

    plansza1.movePlayer(1, new_position, board);
    
    board.printBoard(plansza1);
    plansza1.printFieldInformations(new_position);

    //board.printBoard(plansza1);

    return 0;
}