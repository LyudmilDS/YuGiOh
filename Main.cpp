#include"Write in file.h"
#include"Game.h"
int main()
{
	Player yugi_muto("yugi muto"),pegasus("pegasus");

	yugi_muto.loading_deck("card file.txt",10);
	pegasus.loading_deck("card file.txt", 10);

	Game game(yugi_muto, pegasus);
	game.game();

	return 0;
}
