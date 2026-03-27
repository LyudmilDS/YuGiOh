#ifndef GAME
#define GAME

//system includes
#include<iostream> //cout
#include<string> //string
#include<vector> //vector

//user includes
#include"Card.hpp"
#include"Player.hpp"

class Game
{
private:
	Player m_player1;
	Player m_player2;


public:
	Game() = delete;
	Game(const Player& player1, const Player& player2);

	/// @brief Prepares players' decks for the game
	void loadGame();

	/// @brief Main function that runs the game loop.
	void startGame();

	/// @brief Handles the turn for a specific player.
	void playerTurn(Player& current_player, Player& enemy_player);

	/// @brief In this phase, the player draws a card from their deck.
	void drawPhase(Player& current_player);

	/// @brief In this phase, the player can perform actions such as setting cards or changing a card position.
	int standByPhase(Player& current_player, Player& enemy_player);

	/// @brief In this phase, the player can engage in battles with their opponent.
	void battlePhase(Player&, Player&);

	/// @brief In this phase, the current player's turn ends and the next player's turn begins.
	void endPhase();
};


#endif // !GAME