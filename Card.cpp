//system includes
#include <iostream> //ostream
#include <string> //string

//user includes
#include "Card.hpp"


//-------------------------------------------
//Card Class implementation

Card::Card() : m_name(""), m_position("unplayed"), m_attack(0), m_defence(0)
{
}

Card::Card(const std::string name, int atk, int def) :
	m_name(name),
	m_position("unplayed"),
	m_attack(atk),
	m_defence(def)
{
}

Card::Card(const Card& card) :
	m_name(card.m_name),
	m_position(card.m_position),
	m_attack(card.m_attack),
	m_defence(card.m_defence)
{
}

//-------------------------------------------
//geters

const int Card::getAttack() const
{
	return  m_attack;
}
const int Card::getDefence()const
{
	return  m_defence;
}
const std::string Card::getPosition() const
{
	return  m_position;
}
const std::string Card::getName()const
{
	return  m_name;
}

//-------------------------------------------
//seters

void Card::setAttack(int atk)
{
	m_attack = atk;
}
void Card::setDefence(int def)
{
	m_defence = def;
}
void Card::setPosition(const std::string pos)
{
	m_position = pos;
}
void Card::setName(const std::string name)
{
	m_name = name;
}


void Card::changePosition()
{
	if (m_position == "attack")
	{
		m_position = "defence";
	}
	else if (m_position == "defence")
	{
		m_position = "attack";
	}
}

std::ostream& operator<<(std::ostream& stream, const Card& card)
{
	stream << "Name: " << card.m_name << "\n" <<
		"attack: " << card.m_attack << "\t defence:" << card.m_defence << "\n";
	return stream;
}
