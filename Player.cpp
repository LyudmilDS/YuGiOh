//system includes
#include <algorithm> //sort, swap
#include <stdexcept> //std::out_of_range
#include <iostream> //getline, cout
#include <fstream> //ifstream
#include <stdlib.h> //srand, rand
#include <string> //string
#include <time.h> //time
#include <vector> //vector

//user includes
#include "Card.hpp"
#include "Player.hpp"
#include "Saving_to_file.hpp"

#pragma warning(disable  : 4996)

//-------------------------------------------
//Utilities

//the number of all cards saved in the card_file.txt
const int NR_SAVED_CARDS = 16;

//generates a vector of 'NR_SAVED_CARDS' random numbers in the range [0, NR_SAVED_CARDS)
std::vector<int> generate_rand_rows(int nr_rows)
{
	std::vector<int> rows_read_cards(nr_rows);

	srand(time(0));

	for (int i = 0; i < nr_rows; i++)
	{
		rows_read_cards[i] = rand() % NR_SAVED_CARDS;
	}

	//sorting the array of random numbers to make the reading from the file easier
	std::sort(rows_read_cards.begin(), rows_read_cards.end());

	return rows_read_cards;
}

//-------------------------------------------
//Player Class implementation

Player::Player(const std::string& player_name)
{
	m_name = player_name;
	m_live_points = 4000;

	// reserve memory for the vectors to avoid resizing during the game
	m_hand.reserve(5);
	m_field.reserve(5);
	m_deck.reserve(10);
	m_graveyard.reserve(10);
}

Player::Player(const Player& player) :
	m_name(player.m_name),
	m_hand(player.m_hand),
	m_field(player.m_field),
	m_deck(player.m_deck),
	m_graveyard(player.m_graveyard),
	m_live_points(player.m_live_points)
{
	m_hand.reserve(player.m_hand.capacity());
	m_field.reserve(player.m_field.capacity());
	m_deck.reserve(player.m_deck.capacity());
	m_graveyard.reserve(player.m_graveyard.capacity());
}

Player::~Player()
{
	//empty because member variables have build-in deconstructors
}

//-------------------------------------------
//geters

int Player::getLivePoints()
{
	return  m_live_points;
}

std::string& Player::getName()
{
	return  m_name;
}

std::vector<Card>& Player::getHand()
{
	return  m_hand;
}

std::vector<Card>& Player::getField()
{
	return  m_field;
}

std::vector<Card>& Player::getGraveyard()
{
	return  m_graveyard;
}

//-------------------------------------------
//seters

void Player::receiveDamage(int received_damage)
{
	m_live_points -= received_damage;
}

//-------------------------------------------
//printing on the console

void Player::printHand()
{
	std::cout << "Your hand contains:\n\n";

	int nr_card = 1;

	for (std::vector<Card>::iterator it = m_hand.begin(); it != m_hand.end(); ++it)
	{
		std::cout << "Card " << nr_card << ":\n" << * it << "\n";
		nr_card++;
	}
}

void Player::printField()
{
	std::cout << "Your field contains:\n";

	int nr_card = 1;

	for (std::vector<Card>::iterator it = m_field.begin(); it != m_field.end(); ++it)
	{
		std::cout << "Card " << nr_card << ":\n" << *it << "In " << (*it).getPosition() << " position\n\n";
		nr_card++;
	}
}

void Player::printGraveyard()
{
	std::cout << "Your graveyard contains:\n";

	int nr_card = 1;

	for (std::vector<Card>::iterator it = m_graveyard.begin(); it != m_graveyard.end(); ++it)
	{
		std::cout << "Card " << nr_card << ":\n" << *it << "\n";
		nr_card++;
	}
}

//-------------------------------------------
//preparations for the game

void Player::loadingDeck(const int nr_cards_in_deck)
{
	std::vector<int> rows_read_cards = generate_rand_rows(nr_cards_in_deck);
	std::vector<Card> loaded_cards = loadFromFile();

	for (size_t i = 0; i < rows_read_cards.size(); i++)
	{
		m_deck.push_back(loaded_cards[rows_read_cards[i]]);
	}

	shuffleDeck();
}


void Player::shuffleDeck()
{
	srand(time(0));

	for (int i = 0; i < m_deck.size(); ++i)
	{
		int card_for_swaping = rand() % m_deck.size();
		std::swap(m_deck[i], m_deck[card_for_swaping]);
	}
}

//-------------------------------------------
//actions during the game

void Player::draw()
{
	std::cout << "You drew: \n";

	m_hand.push_back(m_deck.back());
	m_deck.pop_back();

	std::cout << lastDrawnCard() << "\n";
}

const Card& Player::lastDrawnCard()
{
	return m_hand[m_hand.size() - 1];
}

void Player::summonCard()
{
	if (m_hand.size() == 0)
	{
		std::cout << "You have no cards in your hand to summon.\n";
		return;
	}

	std::cout << "You chose to summon a card.\n";
	printHand();
	std::cout << "Enter which card you want to summon: ";

	int number_card;

	//validate the input for the card number
	while(true)
	{
		//ignore the newline character left in the input buffer
		std::cin >> number_card;
		std::cin.ignore();

		if (number_card < 1 || number_card > m_hand.size())
		{
			std::cout << "Invalid card number! Enter a number between 1 and " << m_hand.size() << ": ";
		}
		else
		{
			break;
		}
	}

	std::cout << "Enter in what position you want to summon (attack/defence): ";
	std::string position;
	std::getline(std::cin, position);

	//validate the input for the position of the card
	while(true)
	{
		if (position == "attack")
		{
			m_hand[number_card-1].setPosition("attack");
			m_field.push_back(m_hand[number_card-1]);
			m_hand.erase(m_hand.begin() + number_card-1);

			break;
		}
		else if (position == "defence")
		{
			m_hand[number_card-1].setPosition("defence");
			m_field.push_back(m_hand[number_card-1]);
			m_hand.erase(m_hand.begin() + number_card-1);

			break;
		}
		else
		{
			std::cout << "Invalid input! Enter 'attack' or 'defence': ";
			std::getline(std::cin, position);
		}
	}

	std::cout <<"\n" <<
		m_field[number_card - 1].getName() << " summoned in " << position << " position.\n\n";

}

void Player::destroyedCard(int card_index)
{
	m_graveyard.push_back(m_field[card_index]);
	m_field.erase(m_field.begin() + card_index);
}

void Player::changeCardPosition()
{
	if (m_field.size() == 0)
	{
		std::cout << "You have no cards on the field to change their position.\n";
		return;
	}

	std::cout << "You chose to change a card's position. \n";
	std::cout << "Your field contains:\n";
	printField();
	std::cout << "Enter the number of the card you want to change its position: ";

	int number_card;

	//ignore the newline character left in the input buffer
	std::cin >> number_card;
	std::cin.ignore();

	m_field[number_card].changePosition();
}