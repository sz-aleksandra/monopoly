#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    string map_choice = "plansza1.txt";

    Board board(map_choice);

    board.setNumberOfPlayers(5); 
    board.printBoard();

    int new_position = 15;
    board.movePlayer(1, new_position);
    board.printBoard();


    board.removePlayer(2);
    board.printBoard();

    //board.printFieldInformations(new_position);
  
    
   // board.printBoard(plansza1);


    return 0;
}