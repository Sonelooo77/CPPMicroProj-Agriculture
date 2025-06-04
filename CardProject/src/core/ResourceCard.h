#include "Card.h"	
#include "Dice.h"


class ResourceCard : public Card {
	private:
  diceTypes
      diceTypeMap;  // map comprenant les types de d�s et le nombre de d�s � lancer pour cette carte : {{{NumMin1, NumMax1}, nombreD�1}, {{NumMin2, NumMax2}, nombreD�2}...}
    public:
        ResourceCard(std::string name, int cost, diceTypes diceMap) : Card(name, cost), diceTypeMap(diceMap) {}
        void play() override;

};