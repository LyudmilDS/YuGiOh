#ifndef MONSTERCARD_HPP
#define MONSTERCARD_HPP

//system includes
#include<iostream> //ostream
#include<string> //string

//user includes
#include "BaseCard.hpp"

class MonsterCard : public BaseCard
{
private:
	std::string m_position;
	int m_attack;
	int m_defence;

public:
	MonsterCard();
	MonsterCard(const MonsterCard& card);
	MonsterCard(const std::string& name, int atk, int def);
	~MonsterCard() = default;


	//geters
	const int getAttack() const;
	const int getDefence() const;
	const std::string& getPosition() const;
	const std::string& getName() const;

	//seters
	void setAttack(int atk);
	void setDefence(int def);
	void setPosition(const std::string& pos);
	void setName(const std::string& name);

	void changePosition();

	friend std::ostream& operator << (std::ostream& stream, const MonsterCard& card);
};


#endif // !MONSTERCARD_HPP