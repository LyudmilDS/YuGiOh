// system includes
#include <iostream> //ostream
#include <string> //string

// user includes
#include "MagicCard.hpp"

//-------------------------------------------
// MagicCard Class implementation

MagicCard::MagicCard() : EffectCard(), m_effect_type(EffectType::BUFF_DEBUFF_ATTACK), m_effect_value(0)
{
}
MagicCard::MagicCard(const std::string& name, 
                    const std::string& effect, 
                    const EffectPolarity effect_polarity, 
                    const EffectType effect_type,
                    const double effect_value) :
	EffectCard(name, effect, effect_polarity),
	m_effect_type(effect_type),
	m_effect_value(effect_value)
{
}

MagicCard::MagicCard(const MagicCard& magic_card) :
	EffectCard(magic_card),
	m_effect_type(magic_card.m_effect_type),
	m_effect_value(magic_card.m_effect_value)
{
}

//-------------------------------------------
//getters

const EffectType MagicCard::getEffectType() const
{
    return m_effect_type;
}

const double MagicCard::getEffectValue() const
{
    return m_effect_value;
}

//-------------------------------------------
//setters

void MagicCard::setEffectType(const EffectType effect_type)
{
    m_effect_type = effect_type;
}

void MagicCard::setEffectValue(const double effect_value)
{
    m_effect_value = effect_value;
}

//-------------------------------------------
//operator overloading

void MagicCard::print(std::ostream& stream) const
{
    stream << "Name: " << getName() << "\n"
           << "Effect: " << getEffect() << "\n"
           << "Effect Type: ";
    
    switch (getEffectType())
    {
        case EffectType::BUFF_DEBUFF_ATTACK:
        {
            if (getEffectPolarity() == EffectPolarity::POSITIVE)
            {
                stream << "Increase Attack with " << getEffectValue() << "\n";
            }
            else
            {
                stream << "Decrease Attack with " << getEffectValue() << "\n";
            }
            break;
        }
        case EffectType::BUFF_DEBUFF_DEFENCE:
        {
            if (getEffectPolarity() == EffectPolarity::POSITIVE)
            {
                stream << "Increase Defence with " << getEffectValue() << "\n";
            }
            else            {
                stream << "Decrease Defence with " << getEffectValue() << "\n";
            }
            break;
        }
        case EffectType::DAMAGE_HEAL:
        {
            if (getEffectPolarity() == EffectPolarity::POSITIVE)
            {
                stream << "Heal with " << getEffectValue() << "\n";
            }
            else
            {
                stream << "Damage with " << getEffectValue() << "\n";
            }
            break;
        }
    }
}
