
#include "board.h"

Field::Field(string tp, string n)
	: field_type(tp), name(n)
{}

string Field::getName()
{
	return name;
}

string Field::getType()
{
	return field_type;
}

void Board::setFieldCoordinates()
{
	fields_coordinates.push_back({ 16, 14 });

	for (int j = 13; j >= 5; j--)
	{
		int i = 16;

		fields_coordinates.push_back({ i,j });
	}

	fields_coordinates.push_back({ 16, 4 });

	for (int i = 15; i >= 7; i--)
	{
		int j = 4;

		fields_coordinates.push_back({ i ,j });
	}

	fields_coordinates.push_back({ 6, 4 });

	for (int j = 5; j <= 13; j++)
	{
		int i = 6;

		fields_coordinates.push_back({ i ,j });
	}

	fields_coordinates.push_back({ 6, 14 });

	for (int i = 7; i <= 15; i++)
	{
		int j = 14;

		fields_coordinates.push_back({ i ,j });
	}
}

Board::Board()
	:board_fields({}), fields_coordinates({}), players_locations({})
{}

Board::Board(string filename, Menu menu)
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
		vector <string > values;
		string value;
		
		while (iss >> value)
		{
			values.push_back(value);
		}

		if (values[0] == "property")
		{
			string type = values[0];
			string name = values[1];
			int price = stoi(values[2]);
			string color = values[3];

			Field* temp_field = new Property(type, name, price, color);
			board_fields.push_back(temp_field);
		}
		else if (values[0] == "special")
		{
			string type = values[0];
			string name = values[1];

			Field* temp_field = new Special(type, name);
			board_fields.push_back(temp_field);
		}
		else if (values[0] == "chest")
		{
			string type = values[0];
			string name = values[1];

			Field* temp_field = new Chest(type, name);
			board_fields.push_back(temp_field);
		}
		else if (values[0] == "penalty")
		{
			string type = values[0];
			string name = values[1];
			int tax_to_pay = stoi(values[2]);

			Field* temp_field = new Penalty(type, name, tax_to_pay);
			board_fields.push_back(temp_field);
		}
		else if (values[0] == "chance")
		{
			string type = values[0];
			string name = values[1];

			Field* temp_field = new Chance(type, name);
			board_fields.push_back(temp_field);
		}
		else if (values[0] == "railroads")
		{
			string type = values[0];
			string name = values[1];
			int purchase_price = stoi(values[2]);

			Field* temp_field = new RailRoads(type, name, purchase_price);
			board_fields.push_back(temp_field);
		}
		else if (values[0] == "utility")
		{
			string type = values[0];
			string name = values[1];
			int purchase_price = stoi(values[2]);

			Field* temp_field = new Utility(type, name, purchase_price);
			board_fields.push_back(temp_field);
		}
	}

	createBoard();
	setFieldCoordinates();

	vector<Player> players = menu.players;
	number_of_players = players.size();

	//ustawienie pozycji N graczy
	for (int i = 0; i < number_of_players; i++)
	{
		int x = fields_coordinates[0][0] + 1 + i;
		int y = fields_coordinates[0][1] + 1 + i;
		players_locations.push_back({ x,y });
	}
}

 
void Board::printFieldInformations(int field_number)
{
	Field* field = board_fields[field_number];
	field->printFieldInfo();
}

void Board::movePlayer(int player, int new_field)
{
	int new_x = 0;
	int new_y = 0;

	vector<int> new_position = fields_coordinates[new_field];
	vector<int> current_position = players_locations[player - 1];

	if (new_field > 0 && new_field < 10)
	{
		new_x = new_position[0] + player;
		new_y = new_position[1];
	}

	else if (new_field > 10 && new_field < 20)
	{
		new_x = new_position[0];
		new_y = new_position[1] - player;
	}

	else if (new_field > 20 && new_field < 30)
	{
		new_x = new_position[0] - player;
		new_y = new_position[1];
	}

	else if (new_field > 30 && new_field <= 39)
	{
		new_x = new_position[0];
		new_y = new_position[1] + player;
	}

	else if (new_field == 0)
	{
		new_x = new_position[0] + player;
		new_y = new_position[1] + player;
	}

	else if (new_field == 10)
	{
		new_x = new_position[0] + player;
		new_y = new_position[1] - player;
	}

	else if (new_field == 20)
	{
		new_x = new_position[0] - player;
		new_y = new_position[1] - player;
	}

	else if (new_field == 30)
	{
		new_x = new_position[0] - player;
		new_y = new_position[1] + player;
	}

	setNewCords(current_position[0], current_position[1], ". ");
	players_locations[player - 1] = { new_x, new_y };
}

Field* Board::get_field(int index)
{
	return board_fields[index];
}

void Board::createBoard()
{
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (i == 6 && j >= 5 && j < 15)
			{
				int number = j + 17;
				board[i][j] = to_string(number);
			}

			else if (i == 16 && j >= 4 && j < 15)
			{
				int number = 15 - j;

				if (number < 10)
					board[i][j] = "0" + to_string(number);
				else
					board[i][j] = to_string(number);
			}

			else if (j == 4 && i > 5 && i <= 15)
			{
				int number = 27 - i;
				board[i][j] = to_string(number);
			}


			else if (j == 14 && i > 5 && i <= 15)
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

void Board::printBoard()
{
	for (int i = 0; i < number_of_players; i++)
	{
		string players = "ABCDEF";
		vector<int> current_position = players_locations[i];

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

void Board::setNewCords(int x, int y, string value)
{
	board[x][y] = value;
}

Property::Property(string tp, string name, int price, string col, int own, int num_houses, int num_hotels)
	:Field(tp, name), purchase_price(price), color(col), owner(own), number_of_houses(num_houses), number_of_hotels(num_hotels)
{}

void Property::printFieldInfo()
{
	cout << "\n name: " << name << "\n purchuse price: " << purchase_price << "\n color: " << color << "\n owner: " << owner << endl;

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

void Property::addHotel()
{
	number_of_hotels++;
}

int Property::getOwner() { return owner; }

int Property::getPurchasePrice() { return purchase_price; }

string Property::getColor() { return color; }

int Property::getNumberOfHouses()
{
	return number_of_houses;
}

int Property::getNumberOfHotels()
{
	return number_of_hotels;
}

void Property::setOwner(int own)
{
	owner = own;
}

Utility::Utility(string tp, string name, int price, int own)
	:Field(tp, name), purchase_price(price), owner(own)
{}

void Utility::printFieldInfo()
{
	cout << "\n name: " << name << "\n purchase price: " << purchase_price << "\n owner: " << owner << endl;
}

int Utility::getPurchasePrice() { return purchase_price; }

int Utility::getOwner() { return owner; }


void Utility::setOwner(int own)
{
	owner = own;
}

Penalty::Penalty(string tp, string name, int tax)
	: Field(tp, name), tax_to_pay(tax)
{}

void Penalty::printFieldInfo()
{
	cout << "\n name: " << name << "\n tax to be paid to bank: " << tax_to_pay << endl;
}


int Penalty::getTaxToPay() { return tax_to_pay; }

Chance::Chance(string tp, string nm)
	:Field(tp, nm)
{}

void Chance::printFieldInfo()
{
	cout << "\n name: " << name << endl;
}

Chest::Chest(string tp, string nm)
	:Field(tp, nm)
{}

void Chest::printFieldInfo()
{
	cout << "\n name: " << name << endl;
}

Special::Special(string tp, string nm)
	:Field(tp, nm)
{}

void Special::printFieldInfo()
{
	cout << "\n name: " << name << endl;
}

RailRoads::RailRoads(string tp, string nm, int price, int own)
	:Field(tp, nm), purchase_price(price), owner(own)
{}

void RailRoads::printFieldInfo()
{
	cout << "\n name: " << name << endl;
}

int RailRoads::getPurchasePrice()
{
	return purchase_price;
}

int RailRoads::getOwner()
{
	return owner;
}

void RailRoads::setOwner(int own)
{
	owner = own;
}
