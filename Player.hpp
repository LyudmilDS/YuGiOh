#ifndef PLAYER_HPP
#define PLAYER_HPP

//system includes
#include<string>
#include<vector>
#include<memory>

//user includes
#include"MonsterCard.hpp"

class Player
{
private:
	std::string m_name;
	std::vector<std::unique_ptr<BaseCard>> m_hand;
	std::vector<std::unique_ptr<BaseCard>> m_field;
	std::vector<std::unique_ptr<BaseCard>> m_deck;
	std::vector<std::unique_ptr<BaseCard>> m_graveyard;
	int m_live_points;

public:
	Player(const std::string& player_name);
	Player(const Player& player) = delete; // Cards cannot be copied
	//member variables have build-in deconstructors
	~Player() = default;

	//getters
	int getLivePoints();
	std::string& getName();
	std::vector<std::unique_ptr<BaseCard>>& getHand();
	std::vector<std::unique_ptr<BaseCard>>& getField();
	std::vector<std::unique_ptr<BaseCard>>& getGraveyard();

	//printing on the console
	void printHand();
	void printField();
	void printGraveyard();

	//preparations for the game

	/// @brief Loads cards from the given file to form the player's deck.
	/// @param file: The path to the binary file containing the cards.
	/// @param nr_cards_in_deck: The number of cards to load into the deck.
	void loadingDeck(const int nr_cards_in_deck);

	/// @brief Shuffles the cards in the player's deck.
	void shuffleDeck();

	//actions during the game

	/// @brief Moves the last card from the deck to the hand.
	void draw();

	const MonsterCard& lastDrawnCard();

	/// @brief Reduces the player's live points by the specified amount.
	/// @param received_damage: The amount of damage to receive.
	void receiveDamage(int received_damage);

	/// @brief Moves a card from the hand to the field and prompts the user
	/// in what position the summoned card to be.
	void summonCard();

	/// @brief Removes a card from the field and adds it to the graveyard.
	/// @param card_index: The index of the card on the field to be destroyed.
	void destroyedCard(int card_index);

	/// @brief Prompts the user which card on the field to swap its position.	
	void changeCardPosition();

	/// @brief Validates if the player can attack by checking field status.
	/// @return true if the player has at least one card in attack position, false otherwise.
	bool canAttack();
};


#endif // !PLAYER_HPP