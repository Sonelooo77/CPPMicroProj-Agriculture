#include <gtest/gtest.h>
#include "Dice.h"
#include "ResourceCard.h"
#include "CardFactory.h"
#include "GameManager.h"
#include "LevelFactory.h"

TEST(TestDice, Roll2D6) {
  Dice d6;
  int result = sumDiceRet(d6.roll(2));
  EXPECT_GE(result, 1);
  EXPECT_LE(result, 12);
}

TEST(TestDice, Roll10D20) {
  Dice d20(1,20); 
  int result = sumDiceRet(d20.roll(10));
  EXPECT_GE(result, 10);
  EXPECT_LE(result, 200);
}

TEST(TestDice,  ConcatenationOperator) { 
	Dice d6;
	Dice d10(1,10);
    diceRet result;
    const diceRet& d6roll = d6.roll(2);
    const diceRet& d10roll = d10.roll(1);
    result = d6roll + d10roll;
    int sum = sumDiceRet(result);
    int sumd6 = sumDiceRet(d6roll);
    int sumd10 = sumDiceRet(d10roll);
    EXPECT_EQ(sum, sumd6 + sumd10);
    EXPECT_EQ(result.size(), 3);
}

TEST(TestCardFactory, ResourceCardFactory) { 
    CardFactory factory("resources/cardstest.xml");
    factory.dump();
    auto carroteCard = factory.createCard("Carrote");
    auto bleCard = factory.createCard("Ble");
    carroteCard->play();
    EXPECT_EQ(carroteCard->getName(), "Carrote");
    EXPECT_EQ(carroteCard->getCost(), 1);
    EXPECT_EQ(bleCard->getName(), "Ble");
    EXPECT_EQ(bleCard->getCost(), 2);

}

TEST(TestLevelFactory, CreateValidLevel) {
  LevelFactory factory("resources/levelstest.xml");

  auto level = factory.createLevel(1);
  EXPECT_NE(level, nullptr);
  EXPECT_EQ(level->getLevelId(), 1);
  EXPECT_EQ(level->getName(), "Easy");
  EXPECT_EQ(level->getMaxCost(), 15);
  EXPECT_EQ(level->getTargetScore(), 20);

  level = factory.createLevel(2);
  EXPECT_NE(level, nullptr);
  EXPECT_EQ(level->getLevelId(), 2);
  EXPECT_EQ(level->getName(), "Medium");
  EXPECT_EQ(level->getMaxCost(), 10);
  EXPECT_EQ(level->getTargetScore(), 35);

  level = factory.createLevel(3);
  EXPECT_NE(level, nullptr);
  EXPECT_EQ(level->getLevelId(), 3);
  EXPECT_EQ(level->getName(), "Hard");
  EXPECT_EQ(level->getMaxCost(), 7);
  EXPECT_EQ(level->getTargetScore(), 40);
}


TEST(TestDeck, DeckInitializesWithCards) {
  CardFactory cardFactory("resources/cardstest.xml");
  LevelFactory levelFactory("resources/levelstest.xml");


  GameManager game;
  game.setCardFactory(&cardFactory);
  game.setLevelFactory(&levelFactory);
  game.startLevel();

  EXPECT_EQ(game.getHandSize(), 5);
}


TEST(TestDeck, DrawCardAlwaysWorks) {
  CardFactory cardFactory("resources/cardstest.xml");
  LevelFactory levelFactory("resources/levelstest.xml");

  GameManager game;
  game.setCardFactory(&cardFactory);
  game.startLevel();

  size_t initialHandSize = game.getHandSize();

  for (int i = 0; i < 50; ++i) {
    game.removeCardFromHand(0);
    game.drawCard();
  }

  EXPECT_EQ(game.getHandSize(), initialHandSize);
}

TEST(TestDeck, RandomnessInDeck) {
  CardFactory cardFactory("resources/cardstest.xml");
  LevelFactory levelFactory("resources/levelstest.xml");

  auto level = levelFactory.createLevel(1);
  GameManager game;
  game.setCardFactory(&cardFactory);
  game.startLevel();

  std::set<std::string> drawnCardNames;

  for (int i = 0; i < 30; ++i) {
    game.removeCardFromHand(0);
    game.drawCard();
    if (game.getHandSize() > 0) {
      drawnCardNames.insert(game.getCardInHand(0)->getName());
    }
  }

  EXPECT_GT(drawnCardNames.size(), 1);
}