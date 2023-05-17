#include "board.h"


Field::Field(int own, string col, string nm, float price)
	:name(nm), price_to_buy(price), owner(own), color(col)
{}

void Field::printFieldInfo()
{
	cout << name << " " << price_to_buy << " " << owner << endl;
}

/* ---------- GETTERS ---------- */
string Field::getName()
{
	return name;
}

float Field::getPrice()
{
	return price_to_buy;
}

int Field::getOwner()
{
	return owner;
}

Property::Property(int own, string col, string nm, float price)
	:Field(own, col), name(nm), price_to_buy(price)
{}

Board::Board()
	:board_fields({}), fields_coordinates({}) {}

Board::Board(string filename)
{
	ifstream file(filename);

	if (!file)
	{
		cout << "Blad pliku z plansza" << endl;
		return;
	}

	string line;

	while (getline(file, line))
	{
		istringstream iss(line);
		string name, color;
		int price, owner;

		if (!(iss >> name >> price >> owner >> color))
		{
			cout << "Blad odczytu" << endl;
			break;
		}

		Field temp_field(owner, color, name, price);
		board_fields.push_back(temp_field);
	}
}

void Board::printFields()
{
	for (Field field : board_fields)
	{
		field.printFieldInfo();
	}
}

BoardDisplay::BoardDisplay(Board actual_board_state)
{
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (i == 5 && j >= 5 && j < 15)
			{	
				int number = j + 16;
				board[i][j] = to_string(number);
			}

			else if (i == 16  && j>=5 && j < 15)
			{
				int number = 15 - j;

				if (number != 10)
					board[i][j] = "0" + to_string(number);
				else
					board[i][j] = to_string(number);
			}

			else if (j == 5 && i >= 5 && i <= 15)
			{
				int number = 26 - i;
				board[i][j] = to_string(number);
			}

			else if (j == 14 && i >= 5 && i <= 15)
			{
				int number = 25 + i;
				board[i][j] = to_string(number);
			}

			else
			{
				board[i][j] = ". ";
			}
		}
	}
}

void BoardDisplay::printBoard()
{
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout << board[i][j] << " ";
			
		}
		cout << endl;
	}
}
