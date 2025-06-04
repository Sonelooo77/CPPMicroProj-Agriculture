#include "Dice.h"


Dice::Dice(int min, int max) : 
    // Constructeur de la classe Dice, initialise les valeurs min et max
    min {min}, 
    max {max}
    {}

diceRet Dice::roll(int diceNb) {
    // Renvoie un vecteur comprenant diceNb résultat de lancer de dé;
  static std::random_device rd;
  static std::default_random_engine e(rd());
  std::uniform_int_distribution<unsigned> u(min, max);
  diceRet ret;
  for (size_t i = 0; i < diceNb; ++i) {
    ret.push_back(u(e));
    std::cout << ret.back() << std::endl;
  }
  return ret;
}

int sumDiceRet(diceRet dices_ret) {
    // Renvoie la somme d'un vecteur de résultats de lancer de dés
  int ret = 0;
  for (int i : dices_ret) {
    ret += i; 
  } 
  return ret;
}

diceRet operator+(const diceRet& a, const diceRet& b) {
  // Renvoie un vecteur contenant les éléments de a suivis de ceux de b
  diceRet result = a;                                 
  result.insert(result.end(), b.begin(), b.end()); 
  return result;
}