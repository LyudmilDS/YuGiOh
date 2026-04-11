#ifndef BASECARD_HPP
#define BASECARD_HPP

//system includes
#include<string> //string
#include<iostream> //ostream

//user includes


class BaseCard
{
protected:
	std::string m_name;

public:
	BaseCard() = default;
	BaseCard(const std::string& name);
	virtual ~BaseCard() = default;

	//getters
	const std::string& getName() const;

	//setters
	void setName(const std::string& name);

	virtual void print(std::ostream& stream) const;

	friend std::ostream& operator<<(std::ostream& stream, const BaseCard& card);
};



#endif // !BASECARD_HPP