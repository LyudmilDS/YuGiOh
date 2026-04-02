//user includes
#include"Game.hpp"
#include"Player.hpp"

int main()
{
     Player yugi_muto("Yugi Muto"), pegasus("Pegasus");
     Game game(yugi_muto, pegasus);

	 game.startGame(yugi_muto, pegasus);

}
