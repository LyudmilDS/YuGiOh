#ifndef MAGICCARD_HPP
#define MAGICCARD_HPP

//system includes
#include <iostream> //ostream
#include <string> //string

//user includes
#include "BaseCard.hpp"


enum class EffectPolarity
{
	POSITIVE,
	NEGATIVE,
};

class MagicCard : public BaseCard
{
private:
	std::string m_effect;
	EffectPolarity m_effect_polarity;

public:
	MagicCard(const std::string& name, const std::string& effect, const EffectPolarity effect_polarity);
	MagicCard(const MagicCard& magic_card);

	//getters
	const std::string& getEffect() const;
	const EffectPolarity getEffectPolarity() const;

	//setters
	void setEffect(const std::string& effect);
	void setEffectPolarity(const EffectPolarity effect_polarity);

};

#endif // !MAGICCARD_HPP
