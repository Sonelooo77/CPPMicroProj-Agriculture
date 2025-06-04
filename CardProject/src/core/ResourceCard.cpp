#include "ResourceCard.h"

void ResourceCard::play() {
    // Utilise la map de dés de la carte afin de calculer un résultat
  diceRet result;
  std::ostringstream oss;
  for (const auto& [diceRange, count] : diceTypeMap) {
      Dice dice(diceRange.first,diceRange.second);
      result = result + dice.roll(count);
    }
  oss << "[" << getName() << "] : ";
  for (int i : result) {
    oss << i << " ";
  }
  int total = sumDiceRet(result);
  oss << "| Total : " << total << std::endl;
  std::cout << oss.str();
}
