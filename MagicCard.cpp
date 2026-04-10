//system includes
#include<iostream> //ostream
#include<string> //string

//user includes
#include "MagicCard.hpp"


//-------------------------------------------
//Magic Card Class implementation

MagicCard::MagicCard(const std::string& name, const std::string& effect) :
	BaseCard(name),
	m_effect(effect)
{
}

MagicCard::MagicCard(const MagicCard& magic_card) :
	BaseCard(magic_card),
	m_effect(magic_card.m_effect)
{
}

//-------------------------------------------
//getters

const std::string& MagicCard::getEffect() const
{
	return m_effect;
}

//-------------------------------------------
//setters

void MagicCard::setEffect(const std::string& effect)
{
	m_effect = effect;
}

//-------------------------------------------
//operator overload

std::ostream& operator << (std::ostream& stream, const MagicCard& magic_card)
{
	stream << "Magic Card Name: " << magic_card.m_name << "\n" <<
		"Effect: " << magic_card.m_effect << "\n";

	return stream;
}
