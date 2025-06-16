#ifndef RENDERER_H
#define RENDERER_H


#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include "Card.h"
#include "GameManager.h"

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
                     int lastScore,
                     int scoreDisplayTimer);

void renderGameOver(sf::RenderWindow& window,
                    sf::Font& font,
                    float windowHeight);


#endif //RENDERER_H
