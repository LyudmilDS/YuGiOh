#ifndef SAVING_TO_FILE
#define SAVING_TO_FILE
//system includes
#include <fstream> //ofstream, ifstream
#include <string> //string

//user includes
#include "Card.hpp"


/// @brief Saves the given card in the saved_cards.txt file
/// This is mainly done as a preparation before the game starts.
inline void saveToFile(const Card& saved_card)
{
    std::ofstream file("saved_cards.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error: Could not open file!\n";
        return;
    }

	// Saving cards with separator lines for better readability
    file << saved_card.getName() << "\t"
        << saved_card.getAttack() << "\t"
		<< saved_card.getDefence() << "\n";
}

/// @brief Load all cards from a saved_cards.txt file
/// Returns a vector by value, which is fine, because of move semantics in C++11 and later
inline std::vector<Card> loadFromFile()
{
    std::ifstream file("saved_cards.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open file\n";
        return {};
    }

    int attack = 0, defence = 0;
    std::string name;
    Card curr_loaded_card;
    std::vector<Card> loaded_cards;

    while (std::getline(file, name, '\t'))
    {

        file >> attack >> defence;
		// Clears the newline character left in the input buffer
        file.ignore();

        curr_loaded_card.setName(name);
        curr_loaded_card.setAttack(attack);
        curr_loaded_card.setDefence(defence);

		loaded_cards.push_back(curr_loaded_card);
    }

    return loaded_cards;
}

#endif // !SAVING_TO_FILE