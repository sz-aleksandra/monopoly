#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    string map_choice = "plansza1.txt";
    Board plansza1(map_choice);

    BoardDisplay board(plansza1);
    board.printBoard();
    plansza1.printFields();

    return 0;
}