#pragma once
#include <vector>
#include <string>
#include <map>
#include "Card.h"
#include "ResourceCard.h"
#include "Dice.h"
#include "pugixml.hpp"

struct CardData {
  std::string name;
  std::string type;
  int cost;
  diceSet cardDiceSet; 
};

class CardFactory {
 private:
  std::vector<CardData> cardDefinitions;
  std::map<std::string, CardData> cardByName;
  void loadXMLfile(const std::string& filename);
  CardData loadResourceCardData(const pugi::xml_node& cardNode);

  public:
  std::vector<std::string> getAvailableCards();
  CardFactory(const std::string& cardsFile);
  void dump();
  std::unique_ptr<Card> createCard(const std::string& cardName);
};