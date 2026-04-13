//system includes
#include<iostream> //cout
#include<memory> //unique_ptr
#include<string> //string
#include<vector> //vector

//user includes
#include"MonsterCard.hpp"
#include "Game.hpp"


//-------------------------------------------
//Game Class implementation

Game::Game(const std::string& player1_name, const std::string& player2_name) :
	m_player1(std::make_unique<Player>(player1_name)),
	m_player2(std::make_unique<Player>(player2_name))
{
}

void Game::startGame()
{
	int turn_nr = 1;

	std::cout << 
		"------------------------------\n" <<
		"|  Prepare for the game. \n" <<
		"|  Loading decks... \n" <<
		"------------------------------\n";

	m_player1.get()->loadingDeck(10);
	m_player2.get()->loadingDeck(10);

	while (true)
	{
		if (turn_nr % 2 == 1)
		{
			std::cout << 
			"------------------------------\n" <<
			"|  Turn " << turn_nr << ":\n" <<
			"|  " << m_player1.get()->getName() <<"(" << m_player1.get()->getLivePoints() << " LP)" << " plays \n" <<
			"------------------------------\n";

			playerTurn(*m_player1.get(), *m_player2.get());
		}
		else
		{
			std::cout << 
			"------------------------------\n" <<
			"|  Turn " << turn_nr << ":\n" <<
			"|  " << m_player2.get()->getName() <<"(" << m_player2.get()->getLivePoints() << " LP)" << " plays \n" <<
			"------------------------------\n";

			playerTurn(*m_player2.get(), *m_player1.get());
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
			std::cout << "Invalid input. Enter 'battle' or 'end': ";
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

	std::cout << 
		"Actions you can do in this phase:\n" <<
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
			std::cin.ignore(10000, '\n');
			if (action >= 1 && action <= 4)
			{
				break;
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		std::cout << "Invalid action! Please enter a number between 1 and 4: ";
	}

	switch (action)
	{
	case 1:
		current_player.playCardFromHand();
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

	// choose attacking card and validate user input
	int curr_player_selected_card = validateCardSelection(
		current_player.getField(), 
		"Enter the card number you want to attack with: ", 
		true);

	// If enemy has no cards on the field, attack directly and end the battle phase
	if(enemy_player.getField().size() == 0)
	{
		auto direct_hit_damage = dynamic_cast<MonsterCard*>(
			current_player.getField()[curr_player_selected_card].get())->getAttack();

		std::cout << 
			"Enemy has no cards on the field. You attack directly and enemy loses " <<
			direct_hit_damage << " LP!\n";

		enemy_player.receiveDamage(direct_hit_damage);
		endPhase();

		return;
	}

	std::cout << "Enemy field contains:\n";
	enemy_player.printField();

	// choose defending card and validate user input
	int enemy_player_selected_card = validateCardSelection(
		enemy_player.getField(),
		"Enter the card number from enemy field you want to attack: ", 
		false);

	auto attacker = dynamic_cast<MonsterCard*>(current_player.getField()[curr_player_selected_card].get());
	auto defender = dynamic_cast<MonsterCard*>(enemy_player.getField()[enemy_player_selected_card].get());

	if (!attacker || !defender) {
		std::cout << "Error: Only monsters can participate in battle.\n";
		return;
	}

	resolveBattle(
		current_player, 
		enemy_player, 
		*attacker, 
		*defender, 
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

int Game::validateCardSelection(const std::vector<std::unique_ptr<BaseCard>>& field, const std::string& prompt, bool requireAttackPosition)
{
	std::cout << prompt;

	int card_index;
	int field_size = field.size();

	// validate user input
	while (true)
	{
		if(std::cin >> card_index)
		{
			// clears '\n' from the input buffer
			std::cin.ignore(10000, '\n');

			if (card_index >= 1 && card_index <= field_size)
			{
				auto monster = dynamic_cast<MonsterCard*>(field[card_index - 1].get());

				if (!monster) { 
					std::cout << "Selected card is not a monster! Please selesect a monster card.\n"; 
					continue; 
				}

				if (requireAttackPosition && monster->getPosition() == "defence")
				{
					std::cout << "You can't attack with a card in defence position. You need to change its position first.\n" <<
						prompt;
					continue;
				}

				break;
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}

		std::cout << "Invalid input! Please enter a number between 1 and " << field_size << ": ";
	}

	// returns 0-based index of the selected card
	return card_index-1;
}

void Game::resolveBattle(Player& current_player, 
						Player& enemy_player, 
						const MonsterCard& attacking_card,
						const MonsterCard& defending_card, 
						int attacking_card_index, 
						int defending_card_index)
{
	if (defending_card.getPosition() == std::string("defence"))
	{
		if (attacking_card.getAttack() > defending_card.getDefence())
		{
			enemy_player.destroyCard(defending_card_index);
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
			enemy_player.destroyCard(defending_card_index);
			enemy_player.receiveDamage(attacking_card.getAttack() - defending_card.getAttack());

			std::cout << "Enemy card is destroyed! Enemy loses " <<
				attacking_card.getAttack() - defending_card.getAttack() << " LP!\n";
		}
		else if (attacking_card.getAttack() == defending_card.getAttack())
		{
			current_player.destroyCard(attacking_card_index);
			enemy_player.destroyCard(defending_card_index);
			std::cout << "Both cards had the same attack power and both are destroyed!\n";
		}
		else if (attacking_card.getAttack() < defending_card.getAttack())
		{
			current_player.destroyCard(attacking_card_index);
			current_player.receiveDamage(defending_card.getAttack() - attacking_card.getAttack());
			std::cout << "Your card attack is less than enemy's card attack. Your card is destroyed and you lose " <<
				defending_card.getAttack() - attacking_card.getAttack() << " LP!\n";
		}
	}
}
