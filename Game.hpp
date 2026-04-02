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

	/// @brief Main function that runs the game loop.
	void startGame(Player& player1, Player& player2);

	/// @brief Handles the turn for a specific player.
	void playerTurn(Player& current_player, Player& enemy_player);

	/// @brief In this phase, the player draws a card from their deck.
	void drawPhase(Player& current_player);

	/// @brief In this phase, the player can perform actions such as setting cards or changing a card position.
	void standByPhase(Player& current_player, Player& enemy_player);

	/// @brief In this phase, the player can engage in battles with their opponent.
	void battlePhase(Player&, Player&);

	/// @brief In this phase, the current player's turn ends and the next player's turn begins.
	void endPhase();

private:
	/// @brief Validates and retrieves a card number from the player's input.
	/// @param field: The field to select a card from.
	/// @param prompt: The message to display when prompting for input.
	/// @param requireAttackPosition: If true, rejects cards in defence position (for attacking cards).
	/// @return The 1-based card index.
	int validateCardSelection(const std::vector<Card>& field, const std::string& prompt, bool requireAttackPosition = false);
	
	/// @brief Resolves the battle between an attacking card and a defending card.
	/// @param current_player: The player whose card is attacking.
	/// @param enemy_player: The player whose card is defending.
	/// @param attacking_card: Reference to the attacking card.
	/// @param defending_card: Reference to the defending card.
	/// @param attacking_card_index: The index of the attacking card on the field.
	/// @param defending_card_index: The index of the defending card on the field.
	void resolveBattle(Player& current_player, Player& enemy_player, const Card& attacking_card, 
		const Card& defending_card, int attacking_card_index, int defending_card_index);
};


#endif // !GAME