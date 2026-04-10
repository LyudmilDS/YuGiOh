#ifndef EFFECTCARD_HPP
#define EFFECTCARD_HPP

//system includes
#include <string> //string

//user includes
#include "BaseCard.hpp"


enum class EffectPolarity
{
	POSITIVE = 1,
	NEGATIVE = -1,
};

class EffectCard : public BaseCard
{
protected:
	std::string m_effect;
	EffectPolarity m_effect_polarity;

public:
	EffectCard();
	EffectCard(const std::string& name, const std::string& effect, const EffectPolarity effect_polarity);
	EffectCard(const EffectCard& effect_card);

	//getters
	const std::string& getEffect() const;
	const EffectPolarity getEffectPolarity() const;

	//setters
	void setEffect(const std::string& effect);
	void setEffectPolarity(const EffectPolarity effect_polarity);

};

#endif // !EFFECTCARD_HPP
