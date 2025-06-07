# CPPMicroProj-Agriculture
A micro-project written in C++ using SFML to emulate a luck-based card game.

# Goal
Gain points by using ressource and tool cards to achieve a defined quota, without exceding a cost.

# Game
5 cards are drawn initially, and each time a card is used, a new card is drawn. Each card has a defined number of dices thrown when the card is used, gaining an amount of point equal to the sum of the dices numbers. Tool cards can help the player to achieve better score. 

# Desgin and optimizations
- The game is designed to be played by a single player, with a simple interface to draw cards and use them.
- The game uses SFML for rendering and input handling, providing a simple graphical interface.
- PugiXML is used for loading card AND LEVEL data from XML files, allowing easy modification and expansion of the game.
- Cards and level are created using a Factory Design Pattern
- Deck is a fixed size vector of card names, that are created only when they are drawn. In this case, a new card name is added to the deck vector without changing its size.
- Card is a abstract class and ResourceCards and ToolCards are derived from Card.