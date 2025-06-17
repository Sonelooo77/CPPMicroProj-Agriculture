#ifndef RENDERER_H
#define RENDERER_H


#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "Card.h"
#include "GameManager.h"
#include "AudioManager.h"

sf::Text showCardScore(const int score, sf::Font& font, int opacity = 255);

void loadTextures(const std::vector<std::string>& cardNames,
                  std::map<std::string, sf::Texture>& textureMap);

void renderInfo(sf::RenderWindow& window,
                sf::Font& font,
                GameManager& game);

void renderRetryText(sf::RenderWindow& window,
                     sf::Font& font);

void renderCards(sf::RenderWindow& window,const std::vector<std::unique_ptr<Card>>& hand,
                 const std::map<std::string, sf::Texture>& textureMap,
                 std::vector<sf::Sprite>& sprites,
                 float windowWidth,
                 float windowHeight);

void renderScoreText(sf::RenderWindow& window,
                     sf::Font& font,
                     const std::vector<sf::Sprite>& sprites,
                     int lastCard,
                     const std::vector<int>& diceResults,
                     int scoreDisplayTimer);

void renderGameOver(sf::RenderWindow& window,
                    sf::Font& font,
                    float windowHeight);

void renderNextLevel(sf::RenderWindow& window,
                    sf::Font& font,
                    float windowHeight,
                    int NextLevelTimer);

void renderDiceRoll(sf::RenderWindow& window,
                     sf::Font& font,
                     float windowHeight,
                     float windowWidth,
                     const std::vector<int>& diceResults,
                     int diceAnimationTime,
                     AudioManager& audioManager);

#endif //RENDERER_H
