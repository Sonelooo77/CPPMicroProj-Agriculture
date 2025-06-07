#include "LevelFactory.h"

#include <iostream>

LevelFactory::LevelFactory(const std::string& configFile) {
  loadFromXML(configFile);
}

void LevelFactory::loadFromXML(const std::string& filename) {
  std::cout << "=== LevelFactory ===" << std::endl;
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename.c_str());

  std::cout << "Loading Level file: " << filename << std::endl;

  if (!result) {
    throw std::runtime_error("Failed to load levels file: " + filename);
  }

  std::cout << "Loaded XML file: " << filename << std::endl;
  std::cout << "----- Levels -----" << std::endl;

  pugi::xml_node root = doc.child("levels");

  for (pugi::xml_node levelNode : root.children("level")) {
    LevelData data = loadLevelData(levelNode);
    levelDataById[data.id] = data;
    std::cout << "Loaded data struct | name : " << data.name << std::endl;
  }
}

LevelData LevelFactory::loadLevelData(const pugi::xml_node& levelNode) {
  LevelData data;
  data.id = levelNode.attribute("id").as_int();
  data.name = levelNode.attribute("name").as_string();
  data.maxCost = levelNode.attribute("maxCost").as_int();
  data.targetScore = levelNode.attribute("targetScore").as_int();
  return data;
}

std::unique_ptr<Level> LevelFactory::createLevel(int levelId) {
  const LevelData& data = levelDataById[levelId];  
  return std::make_unique<Level>(data.id, data.maxCost, data.targetScore,data.name);
}
