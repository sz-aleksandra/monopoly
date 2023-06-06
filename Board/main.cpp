#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    string map_choice = "board_parameters.txt";

    Board plansza1(map_choice);
    BoardDisplay board(plansza1);
    
    board.printBoard(plansza1);
    plansza1.printFields();

    vector<Field*> v = plansza1.get_board_fields();

    plansza1.movePlayer(1, 21, board);
    //board.printBoard(plansza1);

    return 0;
}