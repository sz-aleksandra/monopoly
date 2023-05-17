#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Field
{
protected:
	string color;
	string name;
	float price_to_buy;
	int owner;

public:

	Field(int own = 0, string col = "", string nm ="", float price = 0);
	
	void printFieldInfo();

	/* ---------- GETTERS ---------- */
	string getName();
	float getPrice();
	int getOwner();
};

class Property : public Field
{
private:
	string name;
	float price_to_buy;

public:
	Property(int own = 0, string col = "", string nm = "", float price = 0);
};


class Board
{
private:
	vector <Field> board_fields;
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
