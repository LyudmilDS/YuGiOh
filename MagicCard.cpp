//system includes
#include<iostream> //ostream
#include<string> //string

//user includes
#include "MagicCard.hpp"


//-------------------------------------------
//Magic Card Class implementation

MagicCard::MagicCard(const std::string& name, const std::string& effect) :
	m_name(name),
	m_effect(effect)
{
}

MagicCard::MagicCard(const MagicCard& magic_card) :
	m_name(magic_card.m_name),
	m_effect(magic_card.m_effect)
{
}

//-------------------------------------------
//getters

const std::string& MagicCard::getName() const
{
	return m_name;
}

const std::string& MagicCard::getEffect() const
{
	return m_effect;
}

//-------------------------------------------
//setters

void MagicCard::setName(const std::string& name)
{
	m_name = name;
}

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
