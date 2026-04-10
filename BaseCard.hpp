#ifndef BASECARD_HPP
#define BASECARD_HPP

//system includes
#include<string> //string

//user includes


class BaseCard
{
protected:
	std::string m_name;

public:
	BaseCard() = default;
	BaseCard(const std::string& name);
	~BaseCard() = default;

	//getters
	const std::string& getName() const;

	//setters
	void setName(const std::string& name);
};



#endif // !BASECARD_HPP