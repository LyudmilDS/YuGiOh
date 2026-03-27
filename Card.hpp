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
	Card(const std::string name, int atk, int def);
	Card(const Card& card);

	//geters
	const int getAttack() const;
	const int getDefence() const;
	const std::string getPosition() const;
	const std::string getName() const;

	//seters
	void setAttack(int atk);
	void setDefence(int def);
	void setPosition(const std::string pos);
	void setName(const std::string ime);

	void changePosition();


	friend std::ostream& operator << (std::ostream& stream, const Card& card);
};



#endif // !CARD_H