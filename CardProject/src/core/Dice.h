#pragma once
#include<random>
#include<vector>
#include<iostream>
#include<map>

using diceRet = std::vector<int>;

class Dice {
 private:
	 int min = 1; 
	 int max = 6;
 public:
     Dice() = default;  
	 Dice(int min, int max);
     diceRet roll(int diceNb);
};

diceRet operator+(const diceRet& a, const diceRet& b);
int sumDiceRet(diceRet);