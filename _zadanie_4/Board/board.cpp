#include "board.h"


Field::Field(string n)
	: name(n)
{}

string Field::getName()
{
	return name;
}


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

		Field* temp_field = new Property(name, price, color, owner);
		board_fields.push_back(temp_field);
	}
}

Board::~Board()
{
	for (Field* field : board_fields)
	{
		delete field;
	}
	board_fields.clear();
}

void Board::printFields()
{
	for (Field *field : board_fields)
	{
		field->printFieldInfo();
	}
}

BoardDisplay::BoardDisplay(Board& actual_board_state)
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

Property::Property(string name, float price, string col, int own, int num_houses, int num_hotels)
	:Field(name), purchase_price(price), color(col), owner(own), number_of_houses(num_houses), number_of_hotels(num_hotels)
{}

void Property::printFieldInfo()
{
	cout << "\n name: " << name << "\n purchuse price: " << purchase_price << "\n color: " << color << "\n owner: " << owner;

	if (owner != 0)
	{
		cout << "\n number of houser: " << number_of_houses << "\n number of hotels: " << number_of_hotels << endl;
	}
}

void Property::addHouse()
{
	if (number_of_houses < 4)
	{
		number_of_houses++;
	}
}

Utility::Utility(string name, int own, float price)
	:Field(name), owner(own), purchase_price(price)
{}

void Utility::printFieldInfo()
{
	cout << " name: " << name << "\n purchase price: " << purchase_price << "\n owner: " << owner << endl;
}

PenaltyField::PenaltyField(string name, float tax)
	: Field(name), tax_to_pay(tax)
{}

void PenaltyField::printFieldInfo()
{
	cout << " name: " << name << "\n tax to be paid to bank: " << tax_to_pay << endl;
}
