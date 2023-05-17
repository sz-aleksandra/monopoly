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
	Property(string name = "", float price = 0, string col = "", int own = 0, int num_houses = 0, int num_hotels = 0);

	void printFieldInfo() override;
};


class Board
{
protected:
	vector <Field*> board_fields;
	vector<vector<int>> fields_coordinates;

public:
	Board();
	Board(string filename);

	void printFields();
};
	
class BoardDisplay
{
private:
	string board[22][20];

public:

	BoardDisplay(Board actual_board_state);

	void printBoard();
};
