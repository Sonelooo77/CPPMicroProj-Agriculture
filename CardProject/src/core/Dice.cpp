#include "Dice.h"


Dice::Dice(int min, int max) : 
    min {min}, 
    max {max}
    {}

std::vector<int> Dice::roll(int diceNb) {
    // Renvoie un vecteur comprenant diceNb résultat de lancer de dé;
  static std::random_device rd;
  static std::default_random_engine e(rd());
  std::uniform_int_distribution<unsigned> u(min, max);
  std::vector<int> ret;
  for (size_t i = 0; i < diceNb; ++i) {
    ret.push_back(u(e));
    std::cout << ret.back() << std::endl;
  }
  return ret;
}

int sumDiceRet(std::vector<int> dices) {
    // Renvoie la somme d'un vecteur de résultats de lancer de dés
  int ret = 0;
  for (int i : dices) {
    ret += i; 
  } 
  return ret;
}

std::vector<int> operator+(const std::vector<int>& a,
                           const std::vector<int>& b) {
  std::vector<int> result = a;                      // Copie des éléments de 'a'
  result.insert(result.end(), b.begin(), b.end());  // Ajout des éléments de 'b'
  return result;
}