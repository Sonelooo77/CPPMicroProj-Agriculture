#include "GameManager.h"

#include <iostream>

#include "Card.h"
#include "CardFactory.h"
#include "ResourceCard.h"

#define DECK_SIZE 20
#define HAND_SIZE 5

GameManager::GameManager(int startingLevelId)
    : currentLevelId(startingLevelId),
      currentScore(0),
      currentCost(0),
      gameState(GameState::Playing),
      levelFactory(nullptr),
      cardFactory(nullptr),
      gen(rd()) {
}

void GameManager::setCardFactory(CardFactory* factory) {
  if (!factory) {
    throw std::runtime_error("GameManager : CardFactory cannot be null");
  }
  cardFactory = factory;
}


void GameManager::setLevelFactory(LevelFactory* factory) {
  if (!factory) {
    throw std::runtime_error("GameManager : LevelFactory cannot be null");
  }
  levelFactory = factory;
}

void GameManager::startLevel() {
  if (!cardFactory) {
    throw std::runtime_error("GameManager : CardFactory must be set before starting level");
  }
  if (!levelFactory) {
    throw std::runtime_error("GameManager : LevelFactory must be set before starting level");
  }

  currentLevel = levelFactory->createLevel(currentLevelId);

  currentScore = 0;
  currentCost = 0;
  gameState = GameState::Playing;

  playerHand.clear();
  discardPile.clear();

  initializeDeck();
  dealInitialHand();

  std::cout << "=== Level " << currentLevelId << " '" << currentLevel->getName()
            << "' started ! ===" << std::endl;
  std::cout << "Goal: " << currentLevel->getTargetScore() << " points with a "
            << currentLevel->getMaxCost() << " maxmimal cost." << std::endl;
}

void GameManager::initializeDeck() {
  availableCardNames = cardFactory->getAvailableCards();
  deckCardNames.clear();
  refillDeck();
}

void GameManager::refillDeck() {
  while (deckCardNames.size() < DECK_SIZE) {
    deckCardNames.push_back(getRandomCardName());
  }
}

std::string GameManager::getRandomCardName() {
  std::uniform_int_distribution<size_t> dist(0, availableCardNames.size() - 1);
  return availableCardNames[dist(gen)];
}

void GameManager::dealInitialHand() {
  for (int i = 0; i < 5; ++i) {
    drawCard();
  }
}

bool GameManager::canPlayCard(const Card& card) const {
  if ((currentCost + card.getCost()) <= currentLevel->getMaxCost()) {
    return true;
  }
  return false;
}

bool GameManager::canPlayAnyCard() { 
  for (const auto& c : playerHand) {
    if (canPlayCard(*c)) {
      return true;
    }
  }
  return false; 
}

void GameManager::playCard(Card& card) {
  if (!canPlayCard(card)) {
    if (!canPlayAnyCard()) {
      checkGameState(false);
    }
  }

  currentCost += card.getCost();

  std::cout << "Playing: " << card.getName()
            << " (cost: " << card.getCost() << ")" << std::endl;

  card.play();

  if (card.isResourceCard()) {
    currentScore += card.getLastScore();
    std::cout << "Added score : " << card.getLastScore()
              << " (Total: " << currentScore << "/"
              << currentLevel->getTargetScore() << ")" << std::endl;
  }

  std::cout << "Total cost : " << currentCost << "/"
            << currentLevel->getMaxCost() << std::endl;

  checkGameState();
  if (gameState == GameState::Playing) {
    drawCard();
  }
}

void GameManager::drawCard() {

  if (deckCardNames.size() < 5) {
    refillDeck();
  }

  std::string cardName = deckCardNames.front();
  deckCardNames.erase(deckCardNames.begin());
  deckCardNames.push_back(getRandomCardName());


  auto card = cardFactory->createCard(cardName);
  playerHand.push_back(std::move(card));
  std::cout << "Drawn card: " << playerHand.back()->getName() << std::endl;
}

Card* GameManager::getCardInHand(size_t index) {
  if (index >= playerHand.size()) {
    return nullptr;
  }
  return playerHand[index].get();
}

void GameManager::removeCardFromHand(size_t index) {
  if (index < playerHand.size()) {
    discardPile.push_back(std::move(playerHand[index]));
    playerHand.erase(playerHand.begin() + index);
  }
}

void GameManager::checkGameState(bool canPlay) {
  if (currentScore >= currentLevel->getTargetScore()) {
    gameState = GameState::Won;
    std::cout << "Your farm survived, for today. | Score : " << currentScore << std::endl;
  } else if (!canPlay || currentCost > currentLevel->getMaxCost()) {
    gameState = GameState::Lost;
    std::cout << "Your production is a complete mess and your farm will never be used again. | Cost : " << currentCost << " > " << currentLevel->getMaxCost() << std::endl;
  }
}

bool GameManager::nextLevel() {
  if (gameState != GameState::Won) {
    return false;
  }

  if (!hasNextLevel()) {
    return false;
  }

  int nextLevelId = currentLevelId + 1;

  currentLevelId = nextLevelId;
  std::cout << "Advancing to level " << currentLevelId << " !" << std::endl;
  return true;
}

void GameManager::restart() {
  currentLevelId = 1;
}

bool GameManager::hasNextLevel() const {
  return levelFactory && levelFactory->levelExists(currentLevelId + 1);
}

bool GameManager::isGameCompleted() const {
  return gameState == GameState::Won && !hasNextLevel();
}