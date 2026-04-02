#ifndef MAGIC_CARD_H
#define MAGIC_CARD_H

//system includes
#include<iostream> //ostream
#include<string> //string

class MagicCard
{
private:
	std::string m_name;
	std::string m_effect;

public:
	MagicCard(const std::string name, const std::string effect);
	MagicCard(const MagicCard& magic_card);

	//getters
	const std::string getName() const;
	const std::string getEffect() const;

	//setters
	void setName(const std::string name);
	void setEffect(const std::string effect);

	friend std::ostream& operator << (std::ostream& stream, const MagicCard& magic_card);
};

#endif // !MAGIC_CARD_H
