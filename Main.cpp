//system includes
#include <iostream>
#include <vector>
#include <string>

//user includes
#include"Game.hpp"
#include"Player.hpp"
#include"Card.hpp"
#include"Saving_to_file.hpp"

using namespace std;

int main()
{
     Player yugi_muto("Yugi Muto"), pegasus("Pegasus");
     Game game(yugi_muto, pegasus);

	 game.startGame(yugi_muto, pegasus);

}
