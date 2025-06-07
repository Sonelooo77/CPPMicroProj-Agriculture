#include "Level.h"

Level::Level(int id, int maxCost, int targetScore, const std::string& name)
    : levelId(id),
      maxCost(maxCost),
      targetScore(targetScore),
      levelName(name) {}