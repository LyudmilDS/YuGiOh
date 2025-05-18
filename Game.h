#ifndef GAME
#define GAME
#include"Player.h"

class Game
{
private:
	Player player1,player2;

public:
	Game(const Player&, const Player&);
	void player_turn(Player&,Player&);
	void game();

	void drawPhase(Player&);
	void standByPhase(Player&);
	void battlePhase(Player&,Player&);
	void endPhase();

	const Card searchCard(std::vector<Card>,const char*);
};


#endif // !GAME