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

    //Property* field1 = dynamic_cast<Property*>(board.get_field(39));
    //Property* field2 = dynamic_cast<Property*>(board.get_field(37));

    //field1->setOwner(3);
    //field2->setOwner(2);

    board.removePlayer(2);
    board.printBoard();

    RailRoads* field1 = dynamic_cast<RailRoads*>(board.get_field(5));
    RailRoads* field2 = dynamic_cast<RailRoads*>(board.get_field(15));
    RailRoads* field3 = dynamic_cast<RailRoads*>(board.get_field(25));
    RailRoads* field4 = dynamic_cast<RailRoads*>(board.get_field(35));

    field1->setOwner(2);
    field2->setOwner(3);
    field3->setOwner(3);
    field4->setOwner(1);

    bool a = board.doesPlayerHaveAllFields(3, "blue");
    int b = board.howManyRailroads(4);

    cout << b << endl;

    return 0;
}