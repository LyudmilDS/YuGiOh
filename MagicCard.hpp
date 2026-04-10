#ifndef MAGICCARD_HPP
#define MAGICCARD_HPP

//system includes
#include <iostream> //ostream
#include <string> //string

//user includes
#include "BaseCard.hpp"

class MagicCard : public BaseCard
{
private:
	std::string m_effect;

public:
	MagicCard(const std::string& name, const std::string& effect);
	MagicCard(const MagicCard& magic_card);

	//getters
	const std::string& getEffect() const;

	//setters
	void setEffect(const std::string& effect);

	friend std::ostream& operator << (std::ostream& stream, const MagicCard& magic_card);
};

#endif // !MAGICCARD_HPP
