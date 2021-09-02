#ifndef PLAYER_H
#define PLAYER_H
#include"Card.h"
#include<vector>
#include<fstream>
class Player
{
private:
	char* name;
	int live_points;
	std::vector<Card> deck;
	std::vector<Card> hand;
	std::vector<Card> graveyard;
	std::vector<Card> field;

public:
	Player();
	Player(const char* ime);
	Player(const Player& igrach);
	~Player();
	
	//SETers
	void setlivepoints(int );
	void setname(const char* );

	//GETers
	int getlivepoints();
	char* getname();
	std::vector<Card> getHand();
	std::vector<Card> getField();
	std::vector<Card> getGraveyard();

	//printing
	void print_hand();
	void print_field();
	void print_graveyard();

	//preparations for the game
	void loading_deck(const char*,const int);
	void shuffle_deck();

	//actions during the game	
	void draw();
	void lastDrawnCard();
	void summon();
	void changecard_position(int);
	void destroyed_card(const Card&);

	friend std::ostream& operator<<(std::ostream& stream, const Player& igrach);
};


#endif // !PLAYER_H