//system includes
#include <algorithm> //sort, swap
#include <stdexcept> //std::out_of_range
#include <iostream> //getline, cout
#include <fstream> //ifstream
#include <stdlib.h> //srand, rand
#include <string> //string
#include <time.h> //time
#include <utility> //std::move
#include <vector> //vector

//user includes
#include "MonsterCard.hpp"
#include "Player.hpp"
#include "Saving_to_file.hpp"


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


//-------------------------------------------
//getters

int Player::getLivePoints()
{
	return  m_live_points;
}

std::string& Player::getName()
{
	return  m_name;
}

std::vector<MonsterCard>& Player::getHand()
{
	return  m_hand;
}

std::vector<MonsterCard>& Player::getField()
{
	return  m_field;
}

std::vector<MonsterCard>& Player::getGraveyard()
{
	return  m_graveyard;
}

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

	for (const MonsterCard& card : m_hand)
	{
		std::cout << "Card " << nr_card << ":\n" << card << "\n";
		nr_card++;
	}
}

void Player::printField()
{
	std::cout << "Your field contains:\n";

	int nr_card = 1;

	for (const MonsterCard& card : m_field)
	{
		std::cout << "Card " << nr_card << ":\n" << card << 
			"In " << card.getPosition() << " position\n";
		nr_card++;
	}
}

void Player::printGraveyard()
{
	std::cout << "Your graveyard contains:\n";

	int nr_card = 1;

	for (const MonsterCard& card : m_graveyard)
	{
		std::cout << "Card " << nr_card << ":\n" << card << "\n";
		nr_card++;
	}
}

//-------------------------------------------
//preparations for the game

void Player::loadingDeck(const int nr_cards_in_deck)
{
	std::vector<int> rows_read_cards = generate_rand_rows(nr_cards_in_deck);
	std::vector<MonsterCard> loaded_cards = loadMonsterCardsFromFile();

	for (size_t i = 0; i < rows_read_cards.size(); i++)
	{
		m_deck.push_back(std::move(loaded_cards[rows_read_cards[i]]));
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
	m_hand.push_back(std::move(m_deck.back()));

	std::cout << "You drew:\n" << lastDrawnCard() << "\n";
}

const MonsterCard& Player::lastDrawnCard()
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

	std::cout << "\nYou chose to summon a card.\n";

	printHand();

	std::cout << "Enter which card you want to summon: ";

	// validate user input
	int card_number;
	while(true)
	{
		if(std::cin >> card_number)
		{
			std::cin.ignore();

			if (card_number >= 1 && card_number <= m_hand.size())
			{
				break;
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		std::cout << "Invalid input. Enter a number between 1 and " << m_hand.size() << ": ";
	}
	
	std::cout << "Enter in what position you want to summon (attack/defence): ";

	// validate user input
	std::string position;
	while(true)
	{
		std::getline(std::cin, position);

		if (position == "attack" || position == "defence")
		{
			m_hand[card_number-1].setPosition(position);
			m_field.push_back(std::move(m_hand[card_number-1]));
			m_hand.erase(m_hand.begin() + card_number-1);

			break;
		}

		std::cout << "Invalid input! Enter 'attack' or 'defence': ";
	}
}

void Player::destroyedCard(int card_index)
{
	m_graveyard.push_back(std::move(m_field[card_index]));
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

	// validate user input
	int card_number;
	while(true)
	{
		if(std::cin >> card_number)
		{
			std::cin.ignore();

			if (card_number >= 1 && card_number <= m_field.size())
			{
				m_field[card_number-1].changePosition();
				break;
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
		std::cout << "Invalid input. Enter a number between 1 and " << m_field.size() << ": ";
	}
}

bool Player::canAttack()
{
	// Check if field is empty
	if (m_field.size() == 0)
	{
		std::cout << "You have no cards on the field to attack with. Ending your turn.\n";
		return false;
	}

	// Check if all cards on the field are in defence position
	for (const MonsterCard& card : m_field)
	{
		if (card.getPosition() == "attack")
		{
			return true;
		}
	}

	// All cards are in defence position
	std::cout << "All your cards on the field are in defence position and you can't attack.\n" <<
		"Skipping battle phase.\n";
		
	return false;
}