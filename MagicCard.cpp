// system includes
#include <iostream> //ostream
#include <string> //string

// user includes
#include "MagicCard.hpp"

//-------------------------------------------
// MagicCard Class implementation

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

std::ostream& operator<<(std::ostream& stream, const MagicCard& card)
{
    stream << "Name: " << card.getName() << "\n"
           << "Effect: " << card.getEffect() << "\n"
           << "Effect Type: ";
    
    switch (card.getEffectType())
    {
        case EffectType::BUFF_DEBUFF_ATTACK:
        {
            if (card.getEffectPolarity() == EffectPolarity::POSITIVE)
            {
                stream << "Increase Attack with " << card.getEffectValue() << "\n";
            }
            else
            {
                stream << "Decrease Attack with " << card.getEffectValue() << "\n";
            }
            break;
        }
        case EffectType::BUFF_DEBUFF_DEFENCE:
        {
            if (card.getEffectPolarity() == EffectPolarity::POSITIVE)
            {
                stream << "Increase Defence with " << card.getEffectValue() << "\n";
            }
            else            {
                stream << "Decrease Defence with " << card.getEffectValue() << "\n";
            }
            break;
        }
        case EffectType::DAMAGE_HEAL:
        {
            if (card.getEffectPolarity() == EffectPolarity::POSITIVE)
            {
                stream << "Heal with " << card.getEffectValue() << "\n";
            }
            else
            {
                stream << "Damage with " << card.getEffectValue() << "\n";
            }
            break;
        }
    }
    return stream;
}
