#include "Dice.h"
using namespace std;

int main() { 
  int ret;
  Dice die(6);
  for (int i = 0; i < 3; i++) {
    ret = addDiceRet(die.roll(10));
    cout << "Sum : " << ret << endl;
  }
  
  return 0;
}