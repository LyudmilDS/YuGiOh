//system includes
#include <string> //string

//user includes
#include "EffectCard.hpp"


//-------------------------------------------
//Effect Card Class implementation

EffectCard::EffectCard(const std::string& name, const std::string& effect, const EffectPolarity effect_polarity) :
	BaseCard(name),
	m_effect(effect),
	m_effect_polarity(effect_polarity)
{
}

EffectCard::EffectCard(const EffectCard& effect_card) :
	BaseCard(effect_card),
	m_effect(effect_card.m_effect),
	m_effect_polarity(effect_card.m_effect_polarity)
{
}

//-------------------------------------------
//getters

const std::string& EffectCard::getEffect() const
{
	return m_effect;
}

const EffectPolarity EffectCard::getEffectPolarity() const
{
	return m_effect_polarity;
}

//-------------------------------------------
//setters

void EffectCard::setEffect(const std::string& effect)
{
	m_effect = effect;
}

void EffectCard::setEffectPolarity(const EffectPolarity effect_polarity)
{
	m_effect_polarity = effect_polarity;
}

