#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Board;


class Field
{
protected:
	string name;
	string field_type;

public:
	Field(string tp, string n);
	virtual void printFieldInfo() = 0;

	string getName();
	string getType();
};

class Property : public Field
{
private:

	int purchase_price;
	string color;
	int owner;
	int number_of_houses;
	int number_of_hotels;
	int basic_rent;


public:
	Property(string tp = "", string name = "", int price = 0, string col = "", int rent = 0, int own = 0, int num_houses = 0, int num_hotels = 0);
	void printFieldInfo() override;

	int getOwner();
	int getPurchasePrice();
	string getColor();
	int getNumberOfHouses();
	int getNumberOfHotels();

	void setOwner(int own);
	void addHouse();
	void addHotel();

	int getRent();
};


class Utility : public Field
{
private:
	int purchase_price;
	int owner; 

public:
	Utility(string tp = "", string name = "", int price = 0, int owner = 0);
	void printFieldInfo() override;

	int getPurchasePrice();
	int getOwner();

	void setOwner(int own);
	
	int getRentMultiplier(Board *board);
};

class Penalty : public Field
{
private:
	int tax_to_pay;

public:
	Penalty(string tp = "", string name = "", int tax = 0);
	void printFieldInfo() override;

	int getTaxToPay();
};

class Chance : public Field
{
public:
	Chance(string tp = "", string nm = "");
	void printFieldInfo() override;
};

class Chest : public Field
{
public:
	Chest(string tp = "", string nm = "");
	void printFieldInfo() override;
};

class Special : public Field
{
public:
	Special(string tp = "", string nm = "");
	void printFieldInfo() override;
};

class RailRoads : public Field
{
private:
	int purchase_price;
	int owner;
	int basic_rent;

public:
	RailRoads(string tp = "", string nm = "", int price = 0, int rent = 0, int own = 0);
	void printFieldInfo() override;

	int getPurchasePrice();
	int getOwner();

	int getRent(int player, Board *field);
	void setOwner(int own);
};

class Board
{
protected:
	vector <Field*> board_fields;
	vector<vector<int>> fields_coordinates;
	vector <vector<int >> players_locations;
	string board[22][22];
	string players = "ABCDEF";

	int number_of_players;

	void setFieldCoordinates();

public:
	Board();
	Board(string filename, int number_of_players = 1);

	void printFieldInformations(int field);
	void movePlayer(int player, int new_field);
	Field* get_field(int index);

	void setNumberOfPlayers(int players);

	void createBoard();
	void printBoard();
	void setNewCords(int x, int y, string value);
	void removePlayer(int player);

	bool doesPlayerHaveAllFields(int player, string color);
	int howManyRailroads(int player);
	bool doesOnePlayerHaveAllUtilities();
};