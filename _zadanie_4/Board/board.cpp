#include "board.h"


Field::Field(string n)
	: name(n)
{}

string Field::getName()
{
	return name;
}


void Board::setFieldCoordinates()
{
	fields_coordinates.push_back({ 17, 15 });

	for (int j = 13; j >= 6; j--)
	{
		int i = 17;

		fields_coordinates.push_back({ i,j });
	}

	fields_coordinates.push_back({ 17, 4 });

	for (int i = 15; i >= 6; i--)
	{
		int j = 4;

		fields_coordinates.push_back({ i ,j });
	}

	fields_coordinates.push_back({ 4, 4 });

	for (int j = 6; j <= 13; j++)
	{
		int i = 4;

		fields_coordinates.push_back({ i ,j });
	}

	fields_coordinates.push_back({ 4, 15 });

	for (int i = 6; i <= 15; i++)
	{
		int j = 15;

		fields_coordinates.push_back({ i ,j });
	}
}

Board::Board()
	:board_fields({}), fields_coordinates({}), players_locations({})
{}

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

	setFieldCoordinates();

	//ustawienie pozycji 4 graczy
	for (int i = 0; i < 4; i++)
	{
		int x = fields_coordinates[0][0] + i;
		int y = fields_coordinates[0][1] + i;
		players_locations.push_back({ x,y });
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

void Board::move_player(int player, int new_field, BoardDisplay &board)
{
	int new_x = 0;
	int new_y = 0;

	vector<int> new_position = fields_coordinates[new_field - 1];
	vector<int> current_position = players_locations[player - 1];

	if (new_field > 1 && new_field < 10)
	{
		new_x = new_position[0] + player - 1;
		new_y = new_position[1];
	}

	else if (new_field > 10 && new_field < 21)
	{
		new_x = new_position[0];
		new_y = new_position[1] - player + 1;
	}

	else if (new_field > 21 && new_field < 30)
	{
		new_x = new_position[0] - player + 1;
		new_y = new_position[1];
	}

	else if (new_field > 30 && new_field <= 40)
	{
		new_x = new_position[0];
		new_y = new_position[1] + player - 1;
	}

	else if (new_field == 1)
	{
		new_x = new_position[0] + player - 1;
		new_y = new_position[1] + player - 1;
	}

	else if (new_field == 10)
	{
		new_x = new_position[0] + player - 1;
		new_y = new_position[1] - player + 1;
	}

	else if (new_field == 21)
	{
		new_x = new_position[0] - player + 1;
		new_y = new_position[1] - player + 1;
	}

	else if (new_field == 30)
	{
		new_x = new_position[0] - player + 1;
		new_y = new_position[1] + player -1 ;
	}

	board.setNewCords(current_position[0], current_position[1], ". ");
	players_locations[player - 1] = { new_x, new_y };
}

vector<vector<int>> Board::getPlayersLocations()
{
	return players_locations;
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

void BoardDisplay::printBoard(Board& board_state)
{
	vector<vector<int>> posisions = board_state.getPlayersLocations();

	for (int i = 0; i < 4; i++)
	{
		string players = "ABCD";
		vector<int> current_position = posisions[i];

		board[current_position[0]][current_position[1]] = string(1, players[i]) + " ";
	}

	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout << board[i][j] << " ";
			
		}
		cout << endl;
	}
}

void BoardDisplay::setNewCords(int x, int y, string value)
{
	board[x][y] = value;
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
