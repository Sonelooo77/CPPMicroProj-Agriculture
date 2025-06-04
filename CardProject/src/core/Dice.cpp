#include "Dice.h"
#include <time.h>


Dice::Dice(int nb) : maxNb{nb} {}

std::vector<int> Dice::roll(int diceNb) {
    // Renvoie un vecteur comprenant diceNb résultat de lancer de dé;
  static std::random_device rd;
  static std::default_random_engine e(rd());
  static std::uniform_int_distribution<unsigned> u(0, maxNb);
  std::vector<int> ret;
  for (size_t i = 0; i < diceNb; ++i) {
    ret.push_back(u(e));
    std::cout << ret.back() << std::endl;
  }
  return ret;
}

int addDiceRet(std::vector<int> dices) {
    // Renvoie la somme d'un vecteur de résultats de lancer de dés
  int ret = 0;
  for (int i : dices) {
    ret += i; 
  } 
  return ret;
}