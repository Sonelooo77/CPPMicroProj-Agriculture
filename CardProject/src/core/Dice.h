#include<random>
#include<vector>
#include<iostream>

class Dice {
 private:
	 int maxNb;

 public:
	 Dice(int nb);
	 std::vector<int> roll(int diceNb);
};

int addDiceRet(std::vector<int>);