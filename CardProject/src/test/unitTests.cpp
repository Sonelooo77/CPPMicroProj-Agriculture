#include <gtest/gtest.h>
#include "Dice.h"

TEST(TestDice, Roll2D6) {
  Dice d6(6);
  int result = addDiceRet(d6.roll(2));
  EXPECT_GE(result, 1);
  EXPECT_LE(result, 12);
}

TEST(TestDice, Roll10D20) {
  Dice d20(20); 
  int result = addDiceRet(d20.roll(10));
  EXPECT_GE(result, 10);
  EXPECT_LE(result, 200);
}

