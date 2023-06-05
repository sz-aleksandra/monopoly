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

public:
	Field(string n);
	virtual void printFieldInfo() = 0;

	string getName();
};

class Property : public Field
{
private:

	float purchase_price;
	string color;
	int owner;
	int number_of_houses;
	int number_of_hotels;


public:
	Property(string name = "", float price = 0.f, string col = "", int own = 0, int num_houses = 0, int num_hotels = 0);
	void printFieldInfo() override;

	string getName();
	int getOwner();
	float getPurchasePrice();
	string getColor();

	void setOwner(int own);
	void addHouse();
	void addHotel();

};

class Utility : public Field
{
private:
	float purchase_price;
	int owner; 

public:
	Utility(string name = "", int owner = 0, float price = 0.f);
	void printFieldInfo() override;

	float getPurchasePrice();
	int getOwner();
	string getName();

	void setOwner(int own);
};

class PenaltyField : public Field
{
private:
	float tax_to_pay;

public:
	PenaltyField(string name = "", float tax = 0.f);
	void printFieldInfo() override;

	string getName();
	float getTaxToPay();
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
