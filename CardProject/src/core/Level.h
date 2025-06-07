#pragma once
#include <string>

class Level {
 private:
  int levelId;
  int maxCost;
  int targetScore;
  std::string levelName;

 public:
  Level(int id, int maxCost, int targetScore, const std::string& name);

  int getLevelId() const { return levelId; }
  int getMaxCost() const { return maxCost; }
  int getTargetScore() const { return targetScore; }
  const std::string& getName() const { return levelName; }

  bool isValidScore(int score) const { return score >= targetScore; }
  bool isValidCost(int cost) const { return cost <= maxCost; }
};