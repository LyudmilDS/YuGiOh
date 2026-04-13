#ifndef MAGICCARD_HPP
#define MAGICCARD_HPP

//system includes
#include <iostream> //ostream
#include <string> //string

//user includes
#include "EffectCard.hpp"

enum class EffectType
{
    BUFF_DEBUFF_ATTACK,
    BUFF_DEBUFF_DEFENCE,
    DAMAGE_HEAL
};

class MagicCard : public EffectCard
{
private:
    EffectType m_effect_type;
    double m_effect_value;

public:
    MagicCard();
    MagicCard(const std::string& name, 
            const std::string& effect, 
            const EffectPolarity effect_polarity, 
            const EffectType effect_type,
            const double effect_value);
    MagicCard(const MagicCard& magic_card);

    //getters
    const EffectType getEffectType() const;
    const double getEffectValue() const;

    //setters
    void setEffectType(const EffectType effect_type);
    void setEffectValue(const double effect_value);

    void print(std::ostream& stream) const override;
};


#endif // !MAGICCARD_HPP