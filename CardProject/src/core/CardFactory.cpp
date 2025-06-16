#include "CardFactory.h"
#include <iostream>

CardFactory::CardFactory(const std::string& configFile) { loadXMLfile(configFile); }

void CardFactory::loadXMLfile(const std::string& filename) {
  std::cout << "=== CardFactory ===" << std::endl;

  std::cout << "Loading XML file: " << filename << std::endl;

  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename.c_str());
  
  if (!result) {
    throw std::runtime_error("Failed to load XML file: " + filename);
  }

  std::cout << "Loaded XML file: " << filename << std::endl;
  std::cout << "------ Cards ------" << std::endl;
  pugi::xml_node root = doc.child("cards");

  for (pugi::xml_node resourceCard : root.children("resource_card")) {
    CardData data = loadResourceCardData(resourceCard);
    std::cout << "Loaded data struct | name : " << data.name << std::endl;
    data.type = "resource";
    cardDefinitions.push_back(data);
    cardByName[data.name] = data;
  }

  std::cout << "Loaded " << cardDefinitions.size() << " resources cards sucessfully." << std::endl;
  std::cout << "===================" << std::endl;
}

CardData CardFactory::loadResourceCardData(const pugi::xml_node& cardNode) {
    // Renvoie les donn�es organis�es dans une CardData provenant d'un noeud XML de carte ressource
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
     // Cr�e une carte � partir de son nom
  const CardData& data = cardByName[cardName];
     if (data.name.empty()) {
       throw std::runtime_error("Card '" + cardName +"' not found in the factory.");
     }
  std::cout << "Loading card '" << cardName
            << "' | Assiocated data (if exists) : " << cardByName[cardName].name
            << std::endl;
  if (data.type == "resource") {
    return std::make_unique<ResourceCard>(data.name, data.cost, data.cardDiceSet);
  }

}

void CardFactory::dump() {
  // Affiche les cartes disponibles dans la factory
  std::cout << "Cards in the factory : " << std::endl;
  for (const auto& c : cardByName) {
    std::cout << "Card name : " << c.first << std::endl;
  }
}

std::vector<std::string> CardFactory::getAvailableCards() {
  // List les cartes disponibles dans la factory
  std::vector<std::string> availableCards;
  for (const auto& c : cardByName) {
    availableCards.push_back(c.first);
  }
  return availableCards;
}

