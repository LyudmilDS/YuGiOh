# YuGiOh
 The popular card game
  Here you can find my recreation of the popular card game Yu-Gi-Oh. This is a project I did entirely by myself in my leasure time. I started this game for a purpose of exercise. I tried using my programming skills from highschool and first year of my university. There can be found different styles of implementing functions and using char array instead of char* or std::string. This is all made by purpose so I can practise both of them and see how each one works and the differences between them. There are also bad practices because when I was doing this project I didn't know much about how a programme should be built.  
  In my Yu-Gi-Oh game cards have been saved into binary file named "karti.txt". From there random lines are being read and cards with corresponding atributes(name, attack,defence) are created. After that these cards are added into a std::vector of cards that represents the player's deck. When both players have created decks, game starts.
  A game turn consists of a Draw phase, Standby phase, Battle phase and End phase. During each phase different things are done. In draw phase a card from the deck is drawn and is added to the player's hand. During standby phase the player can play the recently drawn card on the field in attack or defence mode. In battle phase a player chooses a card from his field to attack with and then chooses a card from the enemy's field to attack. According to the attack power of the attacking card and the mode(attack/defence) and corresponding atribute(attack/defence) different calculations are made. In end phase all battles end and next player's turn begins.
