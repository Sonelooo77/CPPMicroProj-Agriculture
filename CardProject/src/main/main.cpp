#include <iostream>

#include "CardFactory.h"
#include "GameManager.h"
#include "LevelFactory.h"

int main() {
  CardFactory cardFactory("resources/cardstest.xml");
  LevelFactory levelFactory("resources/levelstest.xml");

  auto level = levelFactory.createLevel(1);
  GameManager game(std::move(level));
  game.setCardFactory(&cardFactory);
  game.startLevel();

  std::cout << "=== ETAT INITIAL ===" << std::endl;
  std::cout << "Niveau: " << game.getLevelName() << std::endl;
  std::cout << "Score: " << game.getCurrentScore() << "/"
            << game.getTargetScore() << std::endl;
  std::cout << "Cout: " << game.getCurrentCost() << "/"
            << game.getCurrentMaxCost() << std::endl;
  do {
  std::cout << "\n=== MAIN ===" << std::endl;
  const auto& hand = game.getPlayerHand();
  for (size_t i = 0; i < hand.size(); ++i) {
    std::cout << i << ". " << hand[i]->getName()
              << " (cout: " << hand[i]->getCost() << ")" << std::endl;
  }

  Card* firstCard = game.getCardInHand(0);
  std::cout << "\nJoue la premiere carte: " << firstCard->getName()
            << std::endl;

  game.playCard(*firstCard);
  game.removeCardFromHand(0);

  std::cout << "\n=== ETAT FINAL ===" << std::endl;
  std::cout << "Score: " << game.getCurrentScore() << "/"
            << game.getTargetScore() << std::endl;
  std::cout << "Cout: " << game.getCurrentCost() << "/"
            << game.getCurrentMaxCost() << std::endl;
  } while (!game.isGameWon() && !game.isGameLost() && game.isGameRunning());

  if (game.isGameWon()) {
    std::cout << "VICTOIRE !" << std::endl;
  } else if (game.isGameLost()) {
    std::cout << "DEFAITE !" << std::endl;
  }
  return 0;

}