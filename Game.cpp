//system includes
#include<iostream> //cout
#include<string> //string
#include<vector> //vector

//user includes
#include"Card.hpp"
#include "Game.hpp"

Game::Game(const Player& player1, const Player& player2) : m_player1(player1), m_player2(player2)
{
}


void Game::loadGame()
{
	std::cout << "------------------------------\n" <<
		"|  Prepare for the game. \n" <<
		"|  Loading decks... \n" <<
		"------------------------------\n" <<
		"\t" << m_player1.getName() << "  vs  " << m_player2.getName() << "\n";

	m_player1.loadingDeck(10);
	m_player2.loadingDeck(10);
}

void Game::startGame()
{
	int turn_nr = 1;

	loadGame();

	while (true)
	{

		if (turn_nr % 2 == 1)
		{
			std::cout << "------------------------------\n" <<
				"|  Turn " << turn_nr << " |  " << m_player1.getName() <<"'s turn\n" <<
				"------------------------------\n";

			playerTurn(m_player1, m_player2);
		}
		else
		{
			std::cout << "------------------------------\n" <<
				"|  Turn " << turn_nr << " |  " << m_player2.getName() << "'s turn\n" <<
				"------------------------------\n";

			playerTurn(m_player2, m_player1);
		}
		++turn_nr;
	}

}

void Game::playerTurn(Player& current_player, Player& enemy_player)
{
	drawPhase(current_player);
	int action = standByPhase(current_player, enemy_player);

	// TODO: this switch is hard to read. It needs to be replaced with 
	// something more clearer
	switch (action)
	{
	case 1:
	case 2:
	{
		std::cout << "Actions you can still do this turn:\n" <<
			"3. Enter Battle phase.\n" <<
			"4. End your turn.\n" <<
			"\n" <<
			"Enter action: ";

		std::cin >> action;
		std::cin.ignore();

		break;
	}
	case 3:
	case 4:
	{
		action = 5;
		break;
	}
	default:
		std::cout << "Invalid StandBy phase!\n";

		break;
	}

	if (action == 3)
	{
		battlePhase(current_player, enemy_player);
	}
	else if (action == 4)
	{
		endPhase();
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

int Game::standByPhase(Player& current_player, Player& enemy_player)
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

	int action = 0;
	std::cin >> action;
	std::cin.ignore();

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
	default:
		std::cout << "Invalid action. Ending your turn.\n";
		endPhase();
		break;
	}

	return action;
}

void Game::battlePhase(Player& current_player, Player& enemy_player)
{

	//TODO: create a function in Player to validate the curr_player field and move this check there.
	//also add a check if all cards on the field are in defence position, because then the player can't attack and should skip battle phase.
	if (current_player.getField().size() == 0)
	{
		std::cout << "You have no cards on the field to attack with. Skipping Battle phase and ending your turn.\n";
		return;
	}

	std::cout <<
		"------------------------------\n" <<
		"|  Battle phase:\n" <<
		"------------------------------\n";

	current_player.printField();

	std::cout << "Enter the card number you want to attack with: ";

	int curr_player_nr_card;

	while(true)
	{
		std::cin >> curr_player_nr_card;
		std::cin.ignore();

		if (curr_player_nr_card < 0 || curr_player_nr_card > current_player.getField().size())
		{
			std::cout << "Invalid card number. Enter number between 1 and " << current_player.getField().size();
		}
		else if (current_player.getField()[curr_player_nr_card-1].getPosition() == std::string("defence"))
		{
			//TODO, as per the above TODO delete this once the function is created
			if (current_player.getField().size() == 1)
			{
				std::cout << "All your cards on the field are in defence position and you can't attack\n"<<
					"Skipping battle phase\n";
				break;
			}
			else
			{
				std::cout << "You can't attack with a card in defence position. You need to change its position first.\n";
			}
		}
		else
		{
			break;
		}
	}

	//TODO, as per the above todo, execute this only if the there is at least one card in attack position on the field
	std::cout << "Enemy field contains:\n";
	enemy_player.printField();

	int enemy_player_nr_card;
	std::cout << "Enter the card number from enemy field you want to attack: ";
	std::cin >> enemy_player_nr_card;
	std::cin.ignore();

	if (enemy_player_nr_card < 0 || enemy_player_nr_card > enemy_player.getField().size())
	{
		std::cout << "Invalid card number.\n";
		return;
	}

	Card& attacking_card = current_player.getField()[curr_player_nr_card];
	Card& defending_card = enemy_player.getField()[enemy_player_nr_card];

	if (defending_card.getPosition() == std::string("defence"))
	{
		if (attacking_card.getAttack() > defending_card.getDefence())
		{
			enemy_player.destroyedCard(enemy_player_nr_card);
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
	else
	{
		if (attacking_card.getAttack() > defending_card.getAttack())
		{
			enemy_player.destroyedCard(enemy_player_nr_card);
			enemy_player.receiveDamage(attacking_card.getAttack() - defending_card.getAttack());

			std::cout << "Enemy card is destroyed! Enemy loses " <<
				attacking_card.getAttack() - defending_card.getAttack() << " LP!\n";
		}
		else if (attacking_card.getAttack() == defending_card.getAttack())
		{
			current_player.destroyedCard(curr_player_nr_card);
			enemy_player.destroyedCard(enemy_player_nr_card);
			std::cout << "Both cards had the same attack power and both are destroyed!\n";
		}
		else if (attacking_card.getAttack() < defending_card.getAttack())
		{
			current_player.destroyedCard(curr_player_nr_card);
			current_player.receiveDamage(defending_card.getAttack() - attacking_card.getAttack());
			std::cout << "Your card attack is less than enemy's card attack. Your card is destroyed and you lose " <<
				defending_card.getAttack() - attacking_card.getAttack() << " LP!\n";
		}
	}
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
