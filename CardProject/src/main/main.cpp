#include "Dice.h"
#include "Card.h"
#include "CardFactory.h"
#include "ResourceCard.h"	
using namespace std;

int main() { 
	
	CardFactory cardFactory("res/cardsheet.xml");
	auto carroteCard = cardFactory.createCard("Carrote");
        auto bleCard = cardFactory.createCard("Ble");
    carroteCard->play();
        bleCard->play();


	return 0; }