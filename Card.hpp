#ifndef CARD_H
#define CARD_H

//system includes
#include<iostream> //ostream
#include<string> //string

class Card
{
private:
	std::string m_name;
	std::string m_position;
	int m_attack;
	int m_defence;

public:
	Card();
	Card(const Card& card);
	Card(const std::string& name, int atk, int def);

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


	friend std::ostream& operator << (std::ostream& stream, const Card& card);
};



#endif // !CARD_H