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
    plansza1.movePlayer(2, new_position + 2, board);
    plansza1.movePlayer(3, new_position - 10, board);
    plansza1.movePlayer(4, new_position, board);
    
   // board.printBoard(plansza1);
   

    board.printBoard(plansza1);
    Field * a = plansza1.get_field(new_position);
    plansza1.printFieldInformations(new_position);

    return 0;
}