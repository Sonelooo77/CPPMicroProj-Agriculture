#include "Dice.h"
#include "Card.h"
#include "ResourceCard.h"	
using namespace std;

int main() {
  ResourceCard carrot("Carrot", 1, {{{1, 6}, 2}});
  ResourceCard potato("Potato", 2, {{{1, 3}, 1}, {{7, 12}, 1}});
  carrot.play();
  potato.play();
  return 0;
}