#pragma once
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "Level.h"
#include "LevelFactory.h"

class CardFactory;
class Card;
class ResourceCard;

enum class GameState { Playing, Won, Lost };

class GameManager {
 private:
  std::unique_ptr<Level> currentLevel;
  int currentLevelId;
  int currentScore;
  int currentCost;
  GameState gameState;

  CardFactory* cardFactory;
  LevelFactory* levelFactory;
  std::vector<std::unique_ptr<Card>> playerHand;
  std::vector<std::unique_ptr<Card>> discardPile;

  std::vector<std::string> deckCardNames;
  std::vector<std::string> availableCardNames;
  std::random_device rd;
  std::mt19937 gen;

  void dealInitialHand();
  void checkGameState(bool canPlay = true);
  void initializeDeck();
  void refillDeck();
  std::string getRandomCardName();

 public:
  GameManager(int startingLevelId = 1);

  void setCardFactory(CardFactory* factory);
  void setLevelFactory(LevelFactory* factory);
  void startLevel();

  bool canPlayCard(const Card& card) const;
  bool canPlayAnyCard();
  void playCard(Card& card);
  void drawCard();

  size_t getHandSize() const { return playerHand.size(); }
  const std::vector<std::unique_ptr<Card>>& getPlayerHand() const {
    return playerHand;
  }
  Card* getCardInHand(size_t index);
  void removeCardFromHand(size_t index);

  bool isGameWon() const { return gameState == GameState::Won; }
  bool isGameLost() const { return gameState == GameState::Lost; }
  bool isGameRunning() const { return gameState == GameState::Playing; }

  int getCurrentLevelId() const { return currentLevelId; }
  int getCurrentMaxCost() const { return currentLevel->getMaxCost(); }
  int getCurrentScore() const { return currentScore; }
  int getCurrentCost() const { return currentCost; }
  int getRemainingCost() const {
    return currentLevel->getMaxCost() - currentCost;
  }
  int getTargetScore() const { return currentLevel->getTargetScore(); }
  const std::string& getLevelName() const { return currentLevel->getName(); }

  bool nextLevel();
  void restart();
  bool hasNextLevel() const;
  bool isGameCompleted() const;
};
