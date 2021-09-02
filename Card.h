#ifndef CARD_H
#define CARD_H

#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<string>

class Card
{
private:
	int attack;
	int defence;
	char position[8];
	char* name;

public:
	Card();
	Card(const char* ime);
	Card(const char* ime, int att, int def);
	Card(const Card& karta);
	//GETers
	int getattack()const;
	int getdefence()const;
	const char* getposition()const;
	const char* getname()const;
	//SETers
	void setattack(int att);
	void setdefence(int def);
	void setposition(const char* pos);
	void setname(const char* ime);

	friend std::ostream& operator << (std::ostream& stream, const Card& karta);
};



#endif // !CARD_H

