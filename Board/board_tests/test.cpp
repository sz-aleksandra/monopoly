#include "pch.h"
#include <iostream>
#include "../../Board/board.cpp"


TEST(BoardTests, TestReadingMap) {

  string map_choice = "C:/Users/HARDPC/source/Repos/23l_proi-monopoly/Board/plansza1.txt";
  Board board(map_choice, 5);

  Field* field = board.get_field(0);
  string name = field->getName();
  
  Field* field1 = board.get_field(39);
  string name1 = field1->getName();

   EXPECT_EQ("Start", name);
   EXPECT_EQ("Boardwalk", name1);
}

TEST(BoardTests, TestHowManyRailroads) {

	string map_choice = "C:/Users/HARDPC/source/Repos/23l_proi-monopoly/Board/plansza1.txt";
	Board board(map_choice, 5);


   RailRoads* field1 = dynamic_cast<RailRoads*>(board.get_field(5));
   RailRoads* field2 = dynamic_cast<RailRoads*>(board.get_field(15));
   RailRoads* field3 = dynamic_cast<RailRoads*>(board.get_field(25));
   RailRoads* field4 = dynamic_cast<RailRoads*>(board.get_field(35));

   field1->setOwner(2);
   field2->setOwner(3);
   field3->setOwner(3);
   field4->setOwner(1);


   EXPECT_EQ(1, board.howManyRailroads(2));
   EXPECT_EQ(2, board.howManyRailroads(3));
   EXPECT_EQ(1, board.howManyRailroads(1));
   EXPECT_EQ(0, board.howManyRailroads(4));
}

TEST(BoardTests, TestDoesPlayerHaveAllFields) {

	string map_choice = "C:/Users/HARDPC/source/Repos/23l_proi-monopoly/Board/plansza1.txt";
	Board board(map_choice, 5);

	Property* field1 = dynamic_cast<Property*>(board.get_field(1));
	Property* field2 = dynamic_cast<Property*>(board.get_field(3));


	Property* field3 = dynamic_cast<Property*>(board.get_field(6));
	Property* field4 = dynamic_cast<Property*>(board.get_field(8));
	Property* field5 = dynamic_cast<Property*>(board.get_field(9));


	field1->setOwner(3);
	field2->setOwner(3);

	field3->setOwner(2);
	field4->setOwner(2);
	field5->setOwner(2);
	
	EXPECT_EQ(1, board.doesPlayerHaveAllFields(3, "brown"));
	EXPECT_EQ(1, board.doesPlayerHaveAllFields(2, "white"));

	EXPECT_EQ(0, board.doesPlayerHaveAllFields(3, "white"));
	EXPECT_EQ(0, board.doesPlayerHaveAllFields(4, "red"));

	field1->setOwner(2);

	EXPECT_EQ(0, board.doesPlayerHaveAllFields(3, "brown"));
}