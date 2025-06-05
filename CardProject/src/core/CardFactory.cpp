#include "CardFactory.h"
#include <iostream>

CardFactory::CardFactory(const std::string& configFile) { loadXMLfile(configFile); }

void CardFactory::loadXMLfile(const std::string& filename) {
    // Charge le fichier XML de définition des caractéristiques des cartes
  cardByName.clear();
  cardDefinitions.clear();

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename.c_str());
  
  pugi::xml_node root = doc.child("cards");

  for (pugi::xml_node resourceCard : root.children("resource_card")) {
    CardData data = loadResourceCardData(resourceCard);
    std::cout << "Loaded data struct | name : " << data.name << " | cost : " << data.cost << std::endl;
    data.type = "resource";
    cardDefinitions.push_back(data);
    cardByName[data.name] = data;
  }

  std::cout << "Loaded" << cardDefinitions.size() << " resources cards." << std::endl;

}

CardData CardFactory::loadResourceCardData(const pugi::xml_node& cardNode) {
    // Renvoie les données organisées dans une CardData provenant d'un noeud XML de carte ressource
  CardData data;
  data.name = cardNode.attribute("name").as_string();
  data.cost = cardNode.attribute("cost").as_int();
  for (pugi::xml_node diceNode : cardNode.children("dice")) {
    int min = diceNode.attribute("min").as_int();
    int max = diceNode.attribute("max").as_int();
    int count = diceNode.attribute("count").as_int();
    data.cardDiceSet.push_back({min, max, count});
  }

  return data;

}

std::unique_ptr<Card> CardFactory::createCard(const std::string& cardName) {
  const CardData& data = cardByName[cardName];
  std::cout << "Loading card '" << cardName
            << "' | Assiocated data (if exists) : " << cardByName[cardName].name
            << std::endl;
            

  if (data.type == "resource") {
    return std::make_unique<ResourceCard>(data.name, data.cost, data.cardDiceSet);
  }

}