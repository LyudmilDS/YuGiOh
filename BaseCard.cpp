//system includes
#include <string> //string

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