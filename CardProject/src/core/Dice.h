#include<random>
#include<vector>
#include<iostream>

class Dice {
 private:
	 int min = 1; 
	 int max = 6;
 public:
     Dice() = default;  
	 Dice(int min, int max);
	 std::vector<int> roll(int diceNb);
};

std::vector<int> operator+(const std::vector<int>& a, const std::vector<int>& b);
int sumDiceRet(std::vector<int>);