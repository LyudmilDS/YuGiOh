#ifndef SAVING_TO_FILE
#define SAVING_TO_FILE

//system includes
#include <fstream> //ofstream, ifstream
#include <string> //string

//user includes
#include "MonsterCard.hpp"
#include "MagicCard.hpp"


/// @brief Saves the given MonsterCard in the saved_monster_cards.txt file
/// This is mainly done as a preparation before the game starts.
inline void saveMonsterCardToFile(const MonsterCard& saved_card)
{
    std::ofstream file("saved_monster_cards.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error: Could not open saved_monster_cards.txt!\n";
        return;
    }

	// Saving cards with separator lines for better readability
    file << saved_card.getName() << "\t"
        << saved_card.getAttack() << "\t"
		<< saved_card.getDefence() << "\n";
}

/// @brief Saves the given MagicCard in a separate file - saved_magic_cards.txt
/// This is mainly done as a preparation before the game starts.
inline void saveMagicCardToFile(const MagicCard& saved_card)
{
    std::ofstream file("saved_magic_cards.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Error: Could not open saved_magic_cards.txt!\n";
        return;
    }

    file << saved_card.getName() << "\t"
        << saved_card.getEffect() << "\t"
        << static_cast<int>(saved_card.getEffectPolarity()) << "\t" // Save enum as int
        << static_cast<int>(saved_card.getEffectType()) << "\t"     // Save enum as int
        << saved_card.getEffectValue() << "\n";
}

/// @brief Load all MonsterCards from saved_monster_cards.txt file
/// Returns a vector by value, which is fine, because of move semantics in C++11
inline std::vector<MonsterCard> loadMonsterCardsFromFile()
{
    std::ifstream file("saved_monster_cards.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open saved_monster_cards.txt!\n";
        return {};
    }

    std::vector<MonsterCard> loaded_cards;
    MonsterCard curr_loaded_card;
    std::string name;
    int attack = 0, defence = 0;

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

/// @brief Load all MagicCards from saved_magic_cards.txt file
/// Returns a vector by value, which is fine, because of move semantics in C++11
inline std::vector<MagicCard> loadMagicCardsFromFile()
{
    std::ifstream file("saved_magic_cards.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not open saved_magic_cards.txt!\n";
        return {};
    }

    std::vector<MagicCard> loaded_cards;
    MagicCard curr_loaded_card;
    std::string name, effect;
    int effect_polarity_int, effect_type_int;
    double effect_value;

    while (std::getline(file, name, '\t'))
    {
        std::getline(file, effect, '\t');
        file >> effect_polarity_int >> effect_type_int >> effect_value;
        // Clears the newline character left in the input buffer
        file.ignore();

        curr_loaded_card.setName(name);
        curr_loaded_card.setEffect(effect);
        curr_loaded_card.setEffectPolarity(static_cast<EffectPolarity>(effect_polarity_int));
        curr_loaded_card.setEffectType(static_cast<EffectType>(effect_type_int));
        curr_loaded_card.setEffectValue(effect_value);

        loaded_cards.push_back(curr_loaded_card);
    }

    return loaded_cards;
}

#endif // !SAVING_TO_FILE