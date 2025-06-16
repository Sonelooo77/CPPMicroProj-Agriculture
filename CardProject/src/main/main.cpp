#include <iostream>
#include <thread>
#include <chrono>

#include "CardFactory.h"
#include "GameManager.h"
#include "LevelFactory.h"
#include "main.h"

int main() {
  CardFactory cardFactory("resources/cardsdefinition.xml");
  LevelFactory levelFactory("resources/levelsdefinition.xml");

  GameManager game;
  game.setCardFactory(&cardFactory);
  game.setLevelFactory(&levelFactory);

  game.startLevel();

  while (true) {
    std::cout << "\n=== CURRENT STATE ===" << std::endl;
    std::cout << "Level " << game.getCurrentLevelId() << " - "
              << game.getLevelName() << std::endl;
    std::cout << "Score: " << game.getCurrentScore() << "/"
              << game.getTargetScore() << std::endl;
    std::cout << "Cost: " << game.getCurrentCost() << "/"
              << game.getCurrentMaxCost() << std::endl;

    const auto& hand = game.getPlayerHand();
    for (size_t i = 0; i < hand.size(); ++i) {
      std::cout << i << ". " << hand[i]->getName()
                << " (cost: " << hand[i]->getCost() << ")" << std::endl;
    }

    Card* firstCard = game.getCardInHand(0);
    std::cout << "\nPlayed card: " << firstCard->getName() << std::endl;

    game.playCard(*firstCard);
    game.removeCardFromHand(0);

    if (game.isGameWon()) {
      std::cout << "Level cleared !" << std::endl;
      if (!game.isGameCompleted()) {
        game.nextLevel();
        game.startLevel();
      } else {
        std::cout << "Game won !" << std::endl;
        break;
      }
    } else if (game.isGameLost()) {
      std::cout << "Game lost !" << std::endl;
      game.restart();
      game.startLevel(); 
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}