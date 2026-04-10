#ifndef BASECARD_HPP
#define BASECARD_HPP

//system includes
#include<iostream> //ostream
#include<string> //string

//user includes


class BaseCard
{
protected:
	std::string m_name;

public:
	BaseCard(const std::string& name);

	//getters
	const std::string& getName() const;
};



#endif // !BASECARD_HPP