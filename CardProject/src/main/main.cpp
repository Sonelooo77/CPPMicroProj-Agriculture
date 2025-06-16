#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>

#include "CardFactory.h"
#include "GameManager.h"
#include "LevelFactory.h"
#include "main.h"

// Function that shows the score of the card played
sf::Text showCardScore(const int score, sf::Font& font, int opacity = 255) {
  sf::Text cardScoreText(font);
  cardScoreText.setFillColor(sf::Color(255, 255, 255, opacity));
  std::ostringstream stream;
  stream << "Score: " << score;
  cardScoreText.setString(stream.str());
  cardScoreText.setCharacterSize(20);
  return cardScoreText;
}

int main() {
  CardFactory cardFactory("resources/cardsdefinition.xml");
  LevelFactory levelFactory("resources/levelsdefinition.xml");

  GameManager game;
  game.setCardFactory(&cardFactory);
  game.setLevelFactory(&levelFactory);

  game.startLevel();

  sf::RenderWindow window(sf::VideoMode({1000, 800}), "SFML window");
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);

  sf::Font font;
  if (!font.openFromFile("resources/assets/arial.ttf")) {
    std::cerr << "Error loading font!" << std::endl;
    return -1;
  }

  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("resources/assets/background.png")) {
    std::cerr << "Erreur lors du chargement du Background" << std::endl;
  }
  sf::Sprite backgroundSprite(backgroundTexture);

  const auto& hand = game.getPlayerHand();

  int lastCard = -1;
  int scoreDisplayTimer = 0;
  int lastScore = 0;

  std::map<std::string, sf::Texture> textureMap;
  for (const auto& availableCardName: cardFactory.getAvailableCards()) {
    const std::string& name = availableCardName;
    std::string texturePath = "resources/sprites/" + name + ".png";
    std::cout << "Loading texture for : " << name << std::endl;
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
      std::cerr << "Erreur lors du chargement de " << texturePath << std::endl;
    }
    textureMap[name] = std::move(texture);
  }


  while (window.isOpen())
  {

    window.clear();

    window.draw(backgroundSprite);

    std::vector<sf::Sprite> sprites;

    // Récuperer Taille de la fenetre
    sf::Vector2u windowSize = window.getSize();
    auto windowWidth = static_cast<float>(windowSize.x);
    auto windowHeight = static_cast<float>(windowSize.y);

    // Affichage du Score
    sf::Text info(font);
    info.setCharacterSize(24);
    info.setFillColor(sf::Color::White);
    std::ostringstream stream;
    stream << "Level " << game.getCurrentLevelId() << " - " << game.getLevelName() << "\n"
    << "Score: " << game.getCurrentScore() << "/" << game.getTargetScore() << "\n"
    << "Cost: " << game.getCurrentCost() << "/" << game.getCurrentMaxCost();
    info.setString(stream.str());
    info.setPosition({windowWidth*0.05f, windowHeight*0.05f});
    window.draw(info);
    sf::Text retry(font);
    retry.setCharacterSize(20);
    retry.setFillColor(sf::Color::White);
    retry.setString("Appuyez sur R pour recommencer");
    retry.setPosition({windowWidth*0.65f, windowHeight*0.05f});
    window.draw(retry);


    // Taille des Sprites
    const float cardWidth = windowWidth / 10.f;
    const float cardHeight = windowHeight / 5.f;
    const float cardSpacing = windowWidth / 20.f;

    float scaleX = cardWidth / 75.f;
    float scaleY = cardHeight / 100.f;


    const auto& hand = game.getPlayerHand();

    float totalWidth = hand.size() * cardWidth + (hand.size() - 1) * cardSpacing;
    float startX = (windowWidth - totalWidth) / 2.f;
    float bottom = windowHeight - cardHeight - 0.1f * cardHeight;

    for (size_t i = 0; i < hand.size(); ++i) {
      const std::string& name = hand[i]->getName();
      sf::Sprite sprite(textureMap.at(name));
      sprite.setScale({scaleX, scaleY});
      sprite.setPosition({startX + i * (cardWidth + cardSpacing), bottom});
      sprites.push_back(sprite);
    }

    // Draw the sprites
    for (const auto& sprite : sprites) {
       window.draw(sprite);
    }


    // Event processing
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (event->is<sf::Event::MouseButtonPressed>()) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          for (size_t i = 0; i < sprites.size(); ++i) {
            if (sprites[i].getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
              game.playCard(*hand[i]);
              lastScore = hand[i]->getLastScore();
              game.removeCardFromHand(i);
              scoreDisplayTimer = 60;
              lastCard = i;
            }
          }
        }
      }
    }

    if (scoreDisplayTimer > 0) {
      scoreDisplayTimer--;
      if (lastCard >= 0) {
        sf::Text cardScoreText = showCardScore(lastScore, font, 4.25f*scoreDisplayTimer );
        cardScoreText.setPosition({sprites[lastCard].getPosition().x, sprites[lastCard].getPosition().y - 30.f});
        window.draw(cardScoreText);
      }
    }

    if (game.isGameWon()) {
      std::cout << "Level cleared !" << std::endl;
      if (!game.isGameCompleted()) {
        game.nextLevel();
        game.startLevel();
      } else {
        std::cout << "Game won !" << std::endl;
        break;
      }
    }

    else if (game.isGameLost()) {
      sf::Text gameOverText(font);
      gameOverText.setString("          Game Over\nAppuyez sur R pour recommencer");
      gameOverText.setCharacterSize(20);
      gameOverText.setFillColor(sf::Color::Red);
      sf::FloatRect textRect = gameOverText.getLocalBounds();
      gameOverText.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
      gameOverText.setPosition({windowHeight*0.5f, windowHeight*0.5f});
      gameOverText.setStyle(sf::Text::Bold);
      window.clear();
      window.draw(gameOverText);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
      game.restart();
      game.startLevel();
    }

    window.display();

  }

  return 0;
}

