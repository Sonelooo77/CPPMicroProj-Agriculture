#include "Card.h"	
#include "Dice.h"


class ResourceCard : public Card {
	private:
  diceTypes
      diceTypeMap;  // map comprenant les types de dés et le nombre de dés à lancer pour cette carte : {{{NumMin1, NumMax1}, nombreDé1}, {{NumMin2, NumMax2}, nombreDé2}...}
    public:
        ResourceCard(std::string name, int cost, diceTypes diceMap) : Card(name, cost), diceTypeMap(diceMap) {}
        void play() override;

};