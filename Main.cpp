#include"Write in file.h"
#include"Game.h"
int main()
{
	//these cards are saved in the file
	/*Card kuriboh("kuriboh",300,200),kuriboh2;
	Card yugi("yugi", 1050, 750),yugi2;
	Card cyber_dragon("cyberDragon", 2100, 1600),cyber_dragon2;
	Card gaya("GayaTheSkyWarrior", 2300, 1100),gaya2;
	Card dark_magician("Toon Dark Magician", 2500, 2100);

	Card Vindictive_Magician("Old Vindictive Magician", 450, 600);
	Card Thousand_eyes("Thousand-Eyes Idol", 0, 0);
	Card Senju("Senju of the Thousand Hands", 1400, 1000);
	Card Giant_Soldier("Giant Soldier of Stone", 1300, 2000);
	Card Curse_dragon("Curse of Dragon", 2000, 1500);
	Card Black_luster("Black Luster Soldier", 3000, 2500);
	Card Celtic("Celtic Guardian", 1400, 1200);
	Card Silver_wolf("Silver Fang", 1200, 800);
	Card Illusionist("Illusionist Faceless Mage", 1200, 2200);
	Card Summoned_skul("Summoned Skull", 2500, 1200);
	Card Gemini_elf("Gemini Elf", 1900, 900);*/

	
	/*saving_in_file(kuriboh);
	saving_in_file(yugi);
	saving_in_file(cyber_dragon);
	saving_in_file(gaya);
	saving_in_file(dark_magician);
	saving_in_file(Vindictive_Magician);
	saving_in_file(Thousand_eyes);
	saving_in_file(Senju);
	saving_in_file(Giant_Soldier);
	saving_in_file(Curse_dragon);
	saving_in_file(Black_luster);
	saving_in_file(Celtic);
	saving_in_file(Silver_wolf);
	saving_in_file(Illusionist);
	saving_in_file(Summoned_skul);
	saving_in_file(Gemini_elf);
	*/

	Player yugi_muto("yugi muto"),pegasus("pegasus");

	yugi_muto.loading_deck("karti.txt",10);
	pegasus.loading_deck("karti.txt", 10);

	Game game(yugi_muto, pegasus);
	game.game();

	return 0;
}