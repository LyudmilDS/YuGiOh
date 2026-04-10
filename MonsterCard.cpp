//system includes
#include <iostream> //ostream
#include <string> //string

//user includes
#include "MonsterCard.hpp"


//-------------------------------------------
//MonsterCard Class implementation

MonsterCard::MonsterCard() : m_name(""), m_position("unplayed"), m_attack(0), m_defence(0)
{
}

MonsterCard::MonsterCard(const std::string& name, int atk, int def) :
	m_name(name),
	m_position("unplayed"),
	m_attack(atk),
	m_defence(def)
{
}

MonsterCard::MonsterCard(const MonsterCard& card) :
	m_name(card.m_name),
	m_position(card.m_position),
	m_attack(card.m_attack),
	m_defence(card.m_defence)
{
}

//-------------------------------------------
//geters

const int MonsterCard::getAttack() const
{
	return  m_attack;
}
const int MonsterCard::getDefence()const
{
	return  m_defence;
}
const std::string& MonsterCard::getPosition() const
{
	return  m_position;
}
const std::string& MonsterCard::getName()const
{
	return  m_name;
}

//-------------------------------------------
//seters

void MonsterCard::setAttack(int atk)
{
	m_attack = atk;
}
void MonsterCard::setDefence(int def)
{
	m_defence = def;
}
void MonsterCard::setPosition(const std::string& pos)
{
	m_position = pos;
}
void MonsterCard::setName(const std::string& name)
{
	m_name = name;
}


void MonsterCard::changePosition()
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

std::ostream& operator<<(std::ostream& stream, const MonsterCard& card)
{
	stream << "Name: " << card.m_name << "\n" <<
		"attack: " << card.m_attack << "\t defence:" << card.m_defence << "\n";
	return stream;
}
