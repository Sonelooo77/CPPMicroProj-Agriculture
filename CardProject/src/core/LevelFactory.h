#pragma once
#include <map>
#include <memory>
#include <string>

#include "Level.h"
#include "pugixml.hpp"

struct LevelData {
  int id;
  std::string name;
  int maxCost;
  int targetScore;
};

class LevelFactory {
 private:
  std::map<int, LevelData> levelDataById;

  void loadFromXML(const std::string& filename);
  LevelData loadLevelData(const pugi::xml_node& levelNode);

 public:
  LevelFactory(const std::string& configFile = "res/data/levels.xml");

  std::unique_ptr<Level> createLevel(int levelId);
};
