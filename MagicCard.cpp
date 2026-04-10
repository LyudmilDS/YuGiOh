//system includes
#include <iostream> //ostream
#include <string> //string

//user includes
#include "MagicCard.hpp"


//-------------------------------------------
//Magic Card Class implementation

MagicCard::MagicCard(const std::string& name, const std::string& effect, const EffectPolarity effect_polarity) :
	BaseCard(name),
	m_effect(effect),
	m_effect_polarity(effect_polarity)
{
}

MagicCard::MagicCard(const MagicCard& magic_card) :
	BaseCard(magic_card),
	m_effect(magic_card.m_effect),
	m_effect_polarity(magic_card.m_effect_polarity)
{
}

//-------------------------------------------
//getters

const std::string& MagicCard::getEffect() const
{
	return m_effect;
}

const EffectPolarity MagicCard::getEffectPolarity() const
{
	return m_effect_polarity;
}

//-------------------------------------------
//setters

void MagicCard::setEffect(const std::string& effect)
{
	m_effect = effect;
}

void MagicCard::setEffectPolarity(const EffectPolarity effect_polarity)
{
	m_effect_polarity = effect_polarity;
}

