//system includes
#include<iostream> //cout
#include<string> //string
#include<vector> //vector

//user includes
#include"Card.hpp"
#include "Game.hpp"


//-------------------------------------------
//Game Class implementation

Game::Game(const Player& player1, const Player& player2) : m_player1(player1), m_player2(player2)
{
}

void Game::startGame(Player& player1, Player& player2)
{
	int turn_nr = 1;

	std::cout << "------------------------------\n" <<
		"|  Prepare for the game. \n" <<
		"|  Loading decks... \n" <<
		"------------------------------\n";

	player1.loadingDeck(10);
	player2.loadingDeck(10);

	while (true)
	{
		std::cout << "------------------------------\n" <<
			"|  Turn " << turn_nr << ":\n" <<
			"------------------------------\n";

		if (turn_nr % 2 == 1)
		{
			playerTurn(player1, player2);
		}
		else
		{
			playerTurn(player2, player1);
		}
		++turn_nr;
	}

}

void Game::playerTurn(Player& current_player, Player& enemy_player)
{
	drawPhase(current_player);
	standByPhase(current_player, enemy_player);

	// validate user input
	std::cout << "Would you like to enter in battle phase or in end phase? (enter 'battle' or 'end'): ";
	while(true)
	{
		std::string answer;
		std::getline(std::cin, answer);

		if (answer == "battle")
		{
			battlePhase(current_player, enemy_player);
			break;
		}
		else if (answer == "end")
		{
			endPhase();
			break;
		}
		else
		{
			std::cout << "Invalid input. Enter 'battle' or 'end'.\n";
		}
	}
}

void Game::drawPhase(Player& current_player)
{
	std::cout <<
		"------------------------------\n" <<
		"|  Draw phase:\n" <<
		"------------------------------\n";

	current_player.draw();
}

void Game::standByPhase(Player& current_player, Player& enemy_player)
{
	std::cout <<
		"------------------------------\n" <<
		"|  Standby phase:\n" <<
		"------------------------------\n";

	std::cout << "Actions you can do in this phase:\n" <<
		"1. Summon a card from your hand to the field.\n" <<
		"2. Change the position of a card on the field.\n" <<
		"3. Enter battle phase.\n" <<
		"4. End your turn.\n" <<
		"\n" <<
		"Enter action: ";

	// validate user input
	int action;
	while (true)
	{
		if(std::cin >> action)
		{
			if (action >= 1 && action <= 4)
			{
				std::cin.ignore();
				break;
			}
		}

		std::cin.clear();
		std::cin.ignore(10000, '\n');

		std::cout << "Invalid action. Please enter a number between 1 and 4: ";
	}

	switch (action)
	{
	case 1:
		current_player.summonCard();
		break;
	case 2:
		current_player.changeCardPosition();
		break;
	case 3:
		battlePhase(current_player, enemy_player);
		break;
	case 4:
		endPhase();
		break;
	}
}

void Game::battlePhase(Player& current_player, Player& enemy_player)
{
	std::cout <<
		"------------------------------\n" <<
		"|  Battle phase:\n" <<
		"------------------------------\n";

	// Check if the player can attack, if not skip the battle phase
	if (!current_player.canAttack())
	{
		return;
	}

	current_player.printField();

	// validate user input for selecting attacking card
	int curr_player_selected_card = validateCardSelection(
		current_player.getField(), 
		"Enter the card number you want to attack with: ", 
		true)-1;

	std::cout << "Enemy field contains:\n";
	enemy_player.printField();

	// validate user input for selecting defending card
	int enemy_player_selected_card = validateCardSelection(
		enemy_player.getField(),
		"Enter the card number from enemy field you want to attack: ", 
		false)-1;

	Card& attacking_card = current_player.getField()[curr_player_selected_card];
	Card& defending_card = enemy_player.getField()[enemy_player_selected_card];

	resolveBattle(
		current_player, 
		enemy_player, 
		attacking_card, 
		defending_card, 
		curr_player_selected_card, 
		enemy_player_selected_card);

	endPhase();
}

void Game::endPhase()
{
	std::cout <<
		"------------------------------\n" <<
		"|  End phase:\n" <<
		"------------------------------\n";
	std::cout << "End of your turn. Now it's enemy turn.\n";
}

int Game::validateCardSelection(const std::vector<Card>& field, const std::string& prompt, bool requireAttackPosition)
{
	std::cout << prompt;

	int card_number;
	int field_size = field.size();

	while (true)
	{
		if(std::cin >> card_number)
		{
			std::cin.ignore();

			if (card_number >= 1 && card_number <= field_size)
			{
				if (requireAttackPosition && field[card_number - 1].getPosition() == std::string("defence"))
				{
					std::cout << "You can't attack with a card in defence position. You need to change its position first.\n" <<
						prompt;
					continue;
				}

				break;
			}
		}

		std::cin.clear();
		std::cin.ignore(10000, '\n');

		std::cout << "Invalid input. Please enter a number between 1 and " << field_size << ": ";
	}

	return card_number;
}

void Game::resolveBattle(Player& current_player, 
						Player& enemy_player, 
						const Card& attacking_card,
						const Card& defending_card, 
						int attacking_card_index, 
						int defending_card_index)
{
	if (defending_card.getPosition() == std::string("defence"))
	{
		if (attacking_card.getAttack() > defending_card.getDefence())
		{
			enemy_player.destroyedCard(defending_card_index);
			std::cout << "Enemy card is destroyed!\n";
		}
		else if (attacking_card.getAttack() < defending_card.getDefence())
		{
			current_player.receiveDamage(defending_card.getDefence() - attacking_card.getAttack());

			std::cout << "Your card attack is less than enemy's card defence. You lose " <<
				defending_card.getDefence() - attacking_card.getAttack() << " LP!\n";
		}
		else if (attacking_card.getAttack() == defending_card.getDefence())
		{
			std::cout << "Attacking card has the same attack power as the defending card. Nothing happens.\n";
		}
	}
	else  // defending_card is in attack position
	{
		if (attacking_card.getAttack() > defending_card.getAttack())
		{
			enemy_player.destroyedCard(defending_card_index);
			enemy_player.receiveDamage(attacking_card.getAttack() - defending_card.getAttack());

			std::cout << "Enemy card is destroyed! Enemy loses " <<
				attacking_card.getAttack() - defending_card.getAttack() << " LP!\n";
		}
		else if (attacking_card.getAttack() == defending_card.getAttack())
		{
			current_player.destroyedCard(attacking_card_index);
			enemy_player.destroyedCard(defending_card_index);
			std::cout << "Both cards had the same attack power and both are destroyed!\n";
		}
		else if (attacking_card.getAttack() < defending_card.getAttack())
		{
			current_player.destroyedCard(attacking_card_index);
			current_player.receiveDamage(defending_card.getAttack() - attacking_card.getAttack());
			std::cout << "Your card attack is less than enemy's card attack. Your card is destroyed and you lose " <<
				defending_card.getAttack() - attacking_card.getAttack() << " LP!\n";
		}
	}
}
