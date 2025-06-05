#include "ResourceCard.h"

void ResourceCard::play() {
    // Utilise la map de dés de la carte afin de calculer un résultat
  diceRet result;
  std::ostringstream oss;
  for (const auto& t : diceSet_) {
    Dice dice(std::get<0>(t), std::get<1>(t));
      result = result + dice.roll(std::get<2>(t));
    }
  oss << "[" << getName() << "] : ";
  for (int i : result) {
    oss << i << " ";
  }
  int total = sumDiceRet(result);
  oss << "| Total : " << total << std::endl;
  std::cout << oss.str();
}
