#include "Player.h"
#pragma warning(disable  : 4996)
Player::Player():live_points(4000),name(nullptr)
{
	name = new char[5];
	char _name[5] = "Zane";
	strcpy(name, _name);
}
Player::Player(const char* ime)
{
	delete this->name;

	this->name = new char[strlen(ime)+1];
	strcpy(this->name, ime);
	this->name[strlen(ime)] = '\0';

	this->live_points = 4000;
}
Player::Player(const Player& igrach)
{

	this->name = new char[strlen(igrach.name)+1];
	for (int i = 0; i < strlen(igrach.name); i++)
	{
		this->name[i] = igrach.name[i];
	}
	this->name[strlen(igrach.name)] = '\0';

	this->live_points = igrach.live_points;

	this->deck = igrach.deck;
	this->hand = igrach.hand;
	this->graveyard = igrach.graveyard;
	this->field = igrach.field;
}
Player::~Player()
{
	delete[] name;
}

//GETers
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

//SETers
void Player::setlivepoints(int lp)
{
	this->live_points = lp;
}
void Player::setname(const char* ime)
{
	for (int i = 0; i < strlen(ime); i++)
	{
		this->name[i] = ime[i];
	}
	this->name[strlen(ime)] = '\0';
}

void Player::loading_deck(const char* file_name,const int count_cards)
{
	std::ifstream File;
	File.open(file_name, std::ios::binary);
	if (!File)
	{
		std::cout << "Cannot open the file!";
		return;
	}
	   
	srand(time(0));
	
	int *number_cards = new int[count_cards];//an array that holds 'count_cards' random numbers
	for (int i = 0; i < count_cards; i++)
	{
		number_cards[i] = rand() % 16;//this number represents all the cards saved in the file
		for (int I = 0; I < i; ++I)
		{
			if (number_cards[i] == number_cards[I])
			{
				number_cards[i] = rand() % 16;//
				I=-1;
			}
		}
	}

	std::sort(number_cards,number_cards+count_cards);

	//reading from the file
	int extracted_cards = 0,line=0;
	while(extracted_cards < count_cards)
	{
		char name[35],pos[8], WS,nul;
		int atk, def;

		//reading name
		int I = 0;
		do
		{
			File.read((char*)&name[I], sizeof(char));
			I++;
		} while (name[I-1] != '\0');
		
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
		} while (pos[I-1] != '\0');

		File.read((char*)&nul, 1);

		//checking if the number of the line in the file is one of the random numbers
		for (int j = 0; j < count_cards; j++)
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

//printing 
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


void Player::draw()
{
	hand.push_back(deck.back());
	deck.pop_back();
}


void Player::lastDrawnCard()
{
	std::cout << hand[hand.size()-1];
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
			field.erase(field.begin()+i);
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

void battle_phase(Player& player1,Player& player2)
{
	std::cout << "\tStart of battle phase.Now you can attack and/or change your cards' positions.\n\t\tYour field contains these cards:\n";
	player1.print_field();
	std::cout << "\n\t\tEnemy's field contains:\n";
	player2.print_field();

	std::cout << "Would you like to attack? (yes/no): ";
	std::string answear;
	std::getline(std::cin, answear);

	if (answear == "yes")
	{	
		int your_attacking_card, enemy_defending_card;
		std::cout << "Choose with which card you want to attack (enter it's number i.e. 1,2,3..): ";		
		std::cin >> your_attacking_card;

		Card* your_card = &player1.field[your_attacking_card - 1];

		if (player2.field.empty())
		{
			std::cout << "The enemy has empty field, you attack directly!\n";
			player2.live_points -= your_card->getattack();

			if (player2.live_points <= 0)
			{
				std::cout << "Enemy's live points reached 0. YOU WIN!!\n";
				return;
			}
		}
		else
		{
			std::cout << "Now enter which enemy card you want to attack (1,2,3..): ";
			std::cin >> enemy_defending_card;
			Card* enemy_card = &player2.field[enemy_defending_card - 1];

			if (enemy_card->getposition() == "attack")
			{
				if (your_card->getattack() <= enemy_card->getattack())
				{
					std::cout << "Both monsters had the same attack power, so they got both destroyed\n";
					player1.graveyard.push_back(*your_card);
					player2.graveyard.push_back(*enemy_card);

					player1.field.erase(player1.field.begin() + your_attacking_card - 1);
					player2.field.erase(player2.field.begin() + enemy_defending_card - 1);
				}
			}
			else if (enemy_card->getposition() == "defence")
			{
				if (your_card->getattack() < enemy_card->getdefence())
				{
					std::cout << "Enemy card has higher defence power than your attaking card's attack. You receive " <<
						enemy_card->getdefence() - your_card->getattack() << " damage.\n";
				}
				else if (your_card->getattack() > enemy_card->getdefence())
				{
					std::cout << "You destroyed enemy's defending card.\n";
					player2.graveyard.push_back(*enemy_card);
					player2.field.erase(player2.field.begin() + enemy_defending_card - 1);
				}
				else
				{
					std::cout << "Your attacking monster and enemy's defending monster have equal values.Nothing happened\n";
				}
			}
		}
	}
	else if (answear == "no")
	{
		std::cout << "Now you can change your cards' positions. Enter numbers, one by one, to change the position of that card, or enter 0 to procced to end phase: ";
		int number_card;
		while (std::cin>>number_card)
		{
			if (number_card == 0)
			{
				end_phase();
			}
			else
			{
				player1.changecard_position(number_card - 1);
			}

		}
	}

	end_phase();
}

void end_phase()
{
	std::cout << "You end your turn. Now it's your oponent.\n";
}

std::ostream& operator<<(std::ostream& stream, const Player& igrach)
{
	stream << "Name: " << igrach.name << "\n" <<
		"LP: " << igrach.live_points << "\n";
	return stream;
}