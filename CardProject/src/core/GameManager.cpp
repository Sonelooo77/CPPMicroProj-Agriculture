#include "GameManager.h"

#include <iostream>

#include "Card.h"
#include "CardFactory.h"
#include "ResourceCard.h"

#define DECK_FIXED_SIZE 20
#define HAND_SIZE 5

GameManager::GameManager(std::unique_ptr<Level> level)
    : currentLevel(std::move(level)),
      currentScore(0),
      currentCost(0),
      gameState(GameState::Playing),
      cardFactory(nullptr),
      gen(rd()) {
  if (!currentLevel) {
    throw std::runtime_error("GameManager : Level cannot be null");
  }
}

void GameManager::setCardFactory(CardFactory* factory) {
  if (!factory) {
    throw std::runtime_error("GameManager : CardFactory cannot be null");
  }
  cardFactory = factory;
}

void GameManager::startLevel() {
  if (!cardFactory) {
    throw std::runtime_error("GameManager : CardFactory must be set before starting level");
  }

  currentScore = 0;
  currentCost = 0;
  gameState = GameState::Playing;

  playerHand.clear();
  discardPile.clear();

  initializeDeck();
  dealInitialHand();

  std::cout << "=== Level '" << currentLevel->getName()
            << "' started ! ===" << std::endl;
  std::cout << "Goal: " << currentLevel->getTargetScore()
            << " points with a " << currentLevel->getMaxCost() << " maxmimal cost."
            << std::endl;
}

void GameManager::initializeDeck() {
  availableCardNames = cardFactory->getAvailableCards();
  deckCardNames.clear();
  refillDeck();
}

void GameManager::refillDeck() {
  while (deckCardNames.size() < DECK_FIXED_SIZE) {
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
  return (currentCost + card.getCost()) <= currentLevel->getMaxCost();
}

void GameManager::playCard(Card& card) {
  if (!canPlayCard(card)) {
    throw std::runtime_error("Cannot play card: insufficient remaining cost");
  }

  currentCost += card.getCost();

  std::cout << "Playing: " << card.getName()
            << " (cost: " << card.getCost() << ")" << std::endl;

  card.play();

  auto* resourceCard = dynamic_cast<ResourceCard*>(&card);
  if (resourceCard) {
    currentScore += resourceCard->getLastScore();
    std::cout << "Added score : " << resourceCard->getLastScore()
              << " (Total: " << currentScore << "/"
              << currentLevel->getTargetScore() << ")" << std::endl;
  }

  std::cout << "Total cost : " << currentCost << "/"
            << currentLevel->getMaxCost() << std::endl;

  checkGameState();
}

void GameManager::drawCard() {
  if (playerHand.size() >= 10) {
    return;
  }

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

void GameManager::checkGameState() {
  if (currentScore >= currentLevel->getTargetScore()) {
    gameState = GameState::Won;
    std::cout << "Your farm survived, for today. | Score : " << currentScore << std::endl;
  } else if (currentCost > currentLevel->getMaxCost()) {
    gameState = GameState::Lost;
    std::cout << "Your production is a complete mess and your farm will never be used again. | Cost : " << currentCost << " > " << currentLevel->getMaxCost() << std::endl;
  }
}