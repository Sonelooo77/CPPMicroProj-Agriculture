#include "ResourceCard.h"

void ResourceCard::play() {
    // Utilise la map de dés de la carte afin de calculer un résultat
  diceRet result;
 // std::ostringstream oss;
  lastDice.clear();
  for (const auto& t : diceSet_) {
    Dice dice(std::get<0>(t), std::get<1>(t));
    diceRet diceResult = dice.roll(std::get<2>(t));
    result = result + diceResult;
    for (int i : diceResult) {
      lastDice.push_back(i);
    }
  }
 //  oss << "[" << getName() << "] : ";

  int total = sumDiceRet(result);
 // oss << "| Total : " << total << std::endl;
 // std::cout << oss.str();
  setLastScore(total);
}
