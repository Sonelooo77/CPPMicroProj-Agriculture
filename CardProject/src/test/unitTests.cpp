#include <gtest/gtest.h>
#include "Dice.h"

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

TEST(TestDice, PlusOperator) { 
	Dice d6;
	Dice d10(1,10);
    std::vector<int> result;
    const std::vector<int>& d6roll = d6.roll(2);
    const std::vector<int>& d10roll = d10.roll(1);
    result = d6roll + d10roll;
    int sum = sumDiceRet(result);
    int sumd6 = sumDiceRet(d6roll);
    int sumd10 = sumDiceRet(d10roll);
    EXPECT_EQ(sum, sumd6 + sumd10);
    EXPECT_EQ(result.size(), 3);
}

