#pragma once
#include "Card.h"	
#include "Dice.h"

using diceSet = std::vector<std::tuple<int,int,int>>;  // {{NumMin, NumMax}, nombreDé}

class ResourceCard : public Card {
	private:
        int lastScore;
        diceSet diceSet_; // map comprenant les types de dés et le nombre de dés à lancer pour cette carte : {{{NumMin1, NumMax1}, nombreDé1}, {{NumMin2, NumMax2}, nombreDé2}...}
    public:
        ResourceCard(std::string name_, int cost_, diceSet diceVector_) : Card(name_, cost_), diceSet_(diceVector_) { lastScore = 0; }
        void play() override;
        int getLastScore() const { return lastScore; }
        void setLastScore(int score) { lastScore = score; }
}
;