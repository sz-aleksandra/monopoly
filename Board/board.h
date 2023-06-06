#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Field
{
protected:
	string name;
	string field_type;

public:
	Field(string tp, string n);
	virtual void printFieldInfo() = 0;

	string getName();
};

class Property : public Field
{
private:

	int purchase_price;
	string color;
	int owner;
	int number_of_houses;
	int number_of_hotels;


public:
	Property(string tp = "", string name = "", int price = 0, string col = "", int own = 0, int num_houses = 0, int num_hotels = 0);
	void printFieldInfo() override;

	int getOwner();
	int getPurchasePrice();
	string getColor();

	void setOwner(int own);
	void addHouse();
	void addHotel();

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

public:
	RailRoads(string tp = "", string nm = "", int price = 0, int own = 0);
	void printFieldInfo() override;
};

class BoardDisplay;

class Board
{
protected:
	vector <Field*> board_fields;
	vector<vector<int>> fields_coordinates;
	vector <vector<int >> players_locations;

	void setFieldCoordinates();

public:
	Board();
	Board(string filename);
	~Board();

	void printFields();
	void movePlayer(int player, int new_field, BoardDisplay &board);
	vector<Field*> get_board_fields();

	vector<vector<int>> getPlayersLocations();
	
};
	
class BoardDisplay
{
private:
	string board[22][20];
	
public:

	BoardDisplay(Board& actual_board_state);

	void printBoard(Board& board_state);

	void setNewCords(int x, int y, string value);
};
