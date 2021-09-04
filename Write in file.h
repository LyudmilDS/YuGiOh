#ifndef FILES
#define FILES

#include"Player.h"

void saving_in_file(Card& karta)
{
	std::ofstream File;
	File.open("card file.txt", std::ios::binary | std::ios::app);
	if (!File)
	{
		std::cout << "cannot open the file!";
	}

	int atk = karta.getattack();
	int def = karta.getdefence();
	const char* name = karta.getname();

	const char* pos = karta.getposition();
	//std::cout << "Saving position: " << pos << "\n";

	char WS = '\t', nul = '\0', newline = '\n';

	for (int i = 0; i < strlen(name); ++i)
	{
		File.write((char*)&name[i], sizeof(char));
	}

	File.write((char*)&nul, sizeof(char));

	File.write((char*)&atk, sizeof(int));
	File.write((char*)&WS, sizeof(char));

	File.write((char*)&def, sizeof(int));
	File.write((char*)&WS, sizeof(char));

	for (int i = 0; i < strlen(pos); ++i)
	{
		File.write((char*)&pos[i], sizeof(char));
	}
	File.write((char*)&nul, sizeof(char));


	File.write((char*)&newline, sizeof(char));
	File.close();
}


#endif // !FILES