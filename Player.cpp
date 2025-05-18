#include "Player.h"

#pragma warning(disable  : 4996)

Player::Player() :live_points(4000), name(nullptr)
{
	// by default c++ cannot assign const char to char. A workaround is to used another variable and copy it
	// this->name is char and _name is const char
	this->name = new char[5];
	// '\0' is automatically added at the end, ONLY IF the array is with +1 lenght
	char _name[5] = "Zane";

	// '\0' is transfered successfully
	strcpy(name, _name);
}

Player::Player(const char* player_name)
{
	this->name = new char[strlen(player_name) + 1];

	// '\0' is transfered successfully
	strcpy(this->name, player_name);
	// for safety measures
	this->name[strlen(player_name)] = '\0';

	this->live_points = 4000;
}

Player::Player(const Player& other_player)
{
	this->name = new char[strlen(other_player.name) + 1];

	//this loop is equavalent to strcpy(name, other_player.name);
	//bad practise is to put strlen() in the loop
	int name_lenght = strlen(other_player.name);
	for (int i = 0; i < name_lenght; i++)
	{
		this->name[i] = other_player.name[i];
	}
	// dont forget to save '\0' at the end of a char[]
	this->name[strlen(other_player.name)] = '\0';

	this->live_points = other_player.live_points;

	this->deck = other_player.deck;
	this->hand = other_player.hand;
	this->graveyard = other_player.graveyard;
	this->field = other_player.field;
}

Player::~Player()
{
	//other member variables have build-in deconstructors
	delete[] name;
}

//GETers-------------------------------------------
int Player::getlivepoints()
{
	return this->live_points;
}

char* Player::getname()
{
	return this->name;
}

std::vector<Card> Player::getHand()
{
	return this->hand;
}

std::vector<Card> Player::getField()
{
	return this->field;
}

std::vector<Card> Player::getGraveyard()
{
	return this->graveyard;
}

//SETers---------------------------------------------
void Player::setlivepoints(int lp)
{
	this->live_points = lp;
}

void Player::setname(const char* new_name)
{
	// avoid memory leak. First delete[] the previous poiter then assign a new one
	delete[] this->name;
	this->name = new char[strlen(new_name) + 1];

	//this loop is equavalent to strcpy(name, new_name);
	//bad practise is to put strlen() in the loop
	int name_lenght = strlen(new_name);
	for (int i = 0; i < name_lenght; i++)
	{
		this->name[i] = new_name[i];
	}
	this->name[strlen(new_name)] = '\0';
}

//printing--------------------------------------------------
void Player::print_hand()
{
	std::cout << "The hand contains:\n";
	for (std::vector<Card>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		std::cout << *it << "\n";
	}
}

void Player::print_field()
{
	std::cout << "The field contains:\n";
	for (std::vector<Card>::iterator it = field.begin(); it != field.end(); ++it)
	{
		std::cout << *it << "\n";
	}
}

void Player::print_graveyard()
{
	std::cout << "The graveyard contains:\n";
	for (std::vector<Card>::iterator it = graveyard.begin(); it != graveyard.end(); ++it)
	{
		std::cout << *it << "\n";
	}
}

//preparations for the game---------------------------------
void Player::loading_deck(const char* file_name, const int count_cards_in_deck)
{
	std::ifstream File;
	File.open(file_name, std::ios::binary);
	if (!File)
	{
		std::cout << "Cannot open the file!";
		return;
	}

	srand(time(0));

	int* number_cards = new int[count_cards_in_deck];//an array that holds 'count_cards_in_deck' random numbers

	for (int i = 0; i < count_cards_in_deck; i++)
	{
		number_cards[i] = rand() % 16;//this number represents all the cards saved in the file
		for (int j = 0; j < i; ++j)
		{
			if (number_cards[i] == number_cards[j])
			{
				number_cards[i] = rand() % 16;
				j = -1;
			}
		}
	}

	std::sort(number_cards, number_cards + count_cards_in_deck);

	//reading from the file
	int extracted_cards = 0, line = 0;
	while (extracted_cards < count_cards_in_deck)
	{
		char name[35], pos[8], WS, nul;
		int atk, def;

		//reading name
		int I = 0;
		do
		{
			File.read((char*)&name[I], sizeof(char));
			I++;
		} while (name[I - 1] != '\0');

		//reading attack & defence
		File.read((char*)&atk, sizeof(int));
		File.read((char*)&WS, 1);

		File.read((char*)&def, sizeof(int));
		File.read((char*)&WS, 1);

		//reading position
		I = 0;
		do
		{
			File.read((char*)&pos[I], sizeof(char));
			I++;
		} while (pos[I - 1] != '\0');

		File.read((char*)&nul, 1);

		//checking if the number of the line in the file is one of the random numbers
		for (int j = 0; j < count_cards_in_deck; j++)
		{
			if (line == number_cards[j])
			{
				Card new_card;
				new_card.setattack(atk);
				new_card.setdefence(def);
				new_card.setposition(pos);
				new_card.setname(name);
				deck.push_back(new_card);
				extracted_cards++;
				break;
			}
		}

		line++;//if the number of the line is not among the random numbers, the reading continues
	}
	delete[] number_cards;

	shuffle_deck();
}


void Player::shuffle_deck()
{
	srand(time(0));
	for (int i = 0; i < deck.size(); ++i)
	{
		int card_for_swaping = rand() % deck.size();
		std::swap(deck[i], deck[card_for_swaping]);
	}
}


void Player::draw()
{
	hand.push_back(deck.back());
	deck.pop_back();
}


void Player::lastDrawnCard()
{
	std::cout << hand[hand.size() - 1];
}
void Player::summon()
{
	std::cout << "You chose to play the card. Now enter in what position you'd like to play it (enter 'attack' or 'defence'): ";
	std::string position;
	std::getline(std::cin, position);

	if (position == "attack")
	{
		hand.back().setposition("attack");
		field.push_back(hand.back());
		hand.pop_back();
	}
	else if (position == "defence")
	{
		hand.back().setposition("defence");
		field.push_back(hand.back());
		hand.pop_back();
	}
}

void Player::destroyed_card(const Card& card_to_be_destroyed)
{
	for (int i = 0; i < field.size(); ++i)
	{
		if (field[i].getname() == card_to_be_destroyed.getname())
		{
			graveyard.push_back(field[i]);
			field.erase(field.begin() + i);
		}
	}
}
void Player::changecard_position(int number_card)
{
	//swaps card's position in the field
	Card* curr_card = &field[number_card];
	if (curr_card->getposition() == "attack")
	{
		curr_card->setposition("defence");
	}
	else
	{
		curr_card->setposition("attack");
	}
}

std::ostream& operator<<(std::ostream& stream, const Player& igrach)
{
	stream << "Name: " << igrach.name << "\n" <<
		"LP: " << igrach.live_points << "\n";
	return stream;
}