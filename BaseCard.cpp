//system includes
#include <string> //string
#include <iostream> //ostream

//user includes
#include "BaseCard.hpp"


//-------------------------------------------
//BaseCard Class implementation

BaseCard::BaseCard(const std::string& name) : m_name(name)
{
}

//-------------------------------------------
//getters

const std::string& BaseCard::getName() const
{
	return m_name;
}

//-------------------------------------------
//setters

void BaseCard::setName(const std::string& name)
{
	m_name = name;
}

void BaseCard::print(std::ostream& stream) const
{
	stream << "Name: " << m_name << "\n";
}

std::ostream& operator<<(std::ostream& stream, const BaseCard& card)
{
	card.print(stream);

	return stream;
}