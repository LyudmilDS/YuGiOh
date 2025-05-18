#include "Game.h"

Game::Game(const Player& player1_, const Player& player2_):player1(player1_),player2(player2_)
{
}

void Game::game()
{
	int turn_nr = 1;
	while (true)
	{
		if (turn_nr % 2 == 1)
		{
			player_turn(player1, player2);
		}
		else
		{
			player_turn(player2, player1);
		}
		++turn_nr;
	}

}
void Game::player1_turn(Player& current_player,Player& enemy_player)
{
	drawPhase(current_player);
	standByPhase(current_player);

	std::cout << "Would you like to enter in battle phase or in end phase? (enter 'battle' or 'end'): ";

	std::string answer;
	std::getline(std::cin, answer);

	if (answear == "battle")
	{
		battlePhase(current_player,enemy_player);
	}

	endPhase();
}

void Game::drawPhase(Player& current_player)
{
	current_player.draw();
	std::cout << "You drew \n";
	current_player.lastDrawnCard();
	std::cout << "\n";
}

void Game::standByPhase(Player& current_player)
{
	std::cout << "Would u like to play the card on the field? (enter 'yes' or 'no'): ";

	std::string answear;
	std::getline(std::cin, answear);

	if (answear == "no")
	{
		std::cout << "So you chose the card to remain in your hand.";
		current_player.print_hand();
	}
	else if (answear == "yes")
	{
		current_player.summon();
	}

}
void Game::battlePhase(Player& current_player,Player& enemy_player)
{
	current_player.print_field();
	std::cout << "Enter the name of a card in attack position you'd like to attack with: ";
	std::string answear;
	std::getline(std::cin, answear);

	Card current_player_card = searchCard(current_player.getField(), answear.c_str());
	
	std::cout << "Choose what you will attack from the enemy field:\n";
	enemy_player.print_field();
	std::cout << "Enter the name of the card from enemy field: ";
	std::getline(std::cin, answear);

	Card enemy_player_card = searchCard(enemy_player.getField(), answear.c_str());

	if (enemy_player_card.getposition() == std::string("defence"))
	{
		if (current_player_card.getattack() > enemy_player_card.getdefence())
		{
			enemy_player.destroyed_card(enemy_player_card);
			std::cout << "Enemy card is destroyed!\n";
		}
		else if (current_player_card.getattack() < enemy_player_card.getdefence())
		{
			int difference_between_atk_and_def= enemy_player_card.getdefence() - current_player_card.getattack();
			current_player.setlivepoints(current_player.getlivepoints()-difference_between_atk_and_def);
			std::cout << "Your card attack is less than enemy's card defence. You lose LP!\n";
		}
		else if (current_player_card.getattack() == enemy_player_card.getdefence())
		{
			std::cout << "Nothing happend.\n";
		}
	}
	else// (enemy_player_card.getposition() == "attack")
	{
		int difference_between_both_attacks =  current_player_card.getattack()- enemy_player_card.getattack() ;

		if (current_player_card.getattack() > enemy_player_card.getattack())
		{
			enemy_player.destroyed_card(enemy_player_card);
			enemy_player.setlivepoints(enemy_player.getlivepoints() - difference_between_both_attacks);
			std::cout << "Enemy card is destroyed!\n";
		}
		else if (current_player_card.getattack() == enemy_player_card.getattack())
		{
			current_player.destroyed_card(current_player_card);
			enemy_player.destroyed_card(enemy_player_card);
			std::cout << "Both cards are destroyed!\n";
		}
		else if (current_player_card.getattack() < enemy_player_card.getattack())
		{
			current_player.destroyed_card(current_player_card);
			current_player.setlivepoints(current_player.getlivepoints() + difference_between_both_attacks);
			std::cout << "Your card attack is less than enemy's card attack. Your card is destroyed and you lose LP!\n";
		}
	}
	
}

void Game::endPhase()
{
	std::cout << "End of the turn. Now it's enemy turn.\n";
}

const Card Game::searchCard(std::vector<Card> vector,const char* card_name)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		if (vector[i].getname() == std::string(card_name))
		{
			return vector[i];
		}
	}
}