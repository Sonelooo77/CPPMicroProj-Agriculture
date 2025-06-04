#include "Dice.h"
using namespace std;

int main() { 
  int ret;
  Dice die;
  for (int i = 0; i < 3; i++) {
    ret = sumDiceRet(die.roll(10));
    cout << "Sum : " << ret << endl;
  }
  
  return 0;
}