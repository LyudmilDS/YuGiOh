#include "Card.h"
#pragma warning(disable  : 4996)

Card::Card()
{
	this->attack = 0;
	this->defence = 0;

	this->position[0] = '\0';

	this->name = nullptr;
}
Card::Card(const char* ime)
{
	this->name = new char[strlen(ime)+1];
	strcpy(this->name, ime);
	this->name[strlen(ime)] = '\0';

	this->attack = 0;
	this->defence = 0;

	this->position[0] = 'a';
	this->position[1] = 't';
	this->position[2] = 't';
	this->position[3] = 'a';
	this->position[4] = 'c';
	this->position[5] = 'k';
	this->position[6] = '\0';
}
Card::Card(const char* ime, int att, int def)
{
	delete[]this->name;
	this->name = new char[strlen(ime) + 1];
	strcpy(this->name, ime);
	this->name[strlen(ime)] = '\0';

	this->attack = att;
	this->defence = def;

	this->position[0] = 'a';
	this->position[1] = 't';
	this->position[2] = 't';
	this->position[3] = 'a';
	this->position[4] = 'c';
	this->position[5] = 'k';
	this->position[6] = '\0';
}
Card::Card(const Card& karta)
{
	this->attack = karta.attack;
	this->defence = karta.defence;

	int i = 0;
	for (; i < strlen(karta.position); i++)
	{
		this->position[i] = karta.position[i];
	}
	position[i] = '\0';

	this->name = new char[strlen(karta.name) + 1];
	strcpy(this->name, karta.name);
	this->name[strlen(karta.name)] = '\0';
}

//GETers
int Card::getattack()const
{
	return this->attack;
}
int Card::getdefence()const
{
	return this->defence;
}
const char* Card::getposition()const
{
	return this->position;
}
const char* Card::getname()const
{
	return this->name;
}
//SETers
void Card::setattack(int att)
{
	this->attack = att;
}
void Card::setdefence(int def)
{
	this->defence = def;
}
void Card::setposition(const char* pos)
{
	for (int i = 0; i < strlen(pos); ++i)
	{
		this->position[i] = pos[i];
	}
	this->position[strlen(pos)] = '\0';
}
void Card::setname(const char* ime)
{
	delete[]this->name;
	this->name = new char[strlen(ime) + 1];
	strcpy(this->name, ime);
	this->name[strlen(ime)] = '\0';
}


std::ostream& operator<<(std::ostream& stream, const Card& karta)
{
	stream << "Name: " << karta.name << "\n" <<
			  "attack: " << karta.attack << "\t defence:" << karta.defence <<
		      "\nIn " << karta.position << " mode\n";
	return stream;
}
