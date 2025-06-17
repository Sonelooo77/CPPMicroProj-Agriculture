/* renderer.cpp */
#include "Renderer.h"
#include <iostream>
#include <sstream>
#include <map>
#include "AudioManager.h"
#include <SFML/Graphics.hpp>

#include "Card.h"
#include "GameManager.h"

sf::Text showCardScore(const int score, sf::Font& font, int opacity) {
    sf::Text cardScoreText(font);
    cardScoreText.setFillColor(sf::Color(255, 255, 255, opacity));
    std::ostringstream stream;
    stream << "Farm Power:" << score;
    cardScoreText.setString(stream.str());
    cardScoreText.setCharacterSize(20);
    return cardScoreText;
}

void loadTextures(const std::vector<std::string>& cardNames, std::map<std::string, sf::Texture>& textureMap) {
    for (const auto& name : cardNames) {
        std::string texturePath = "resources/sprites/" + name + ".png";
        std::cout << "Loading texture for : " << name << std::endl;
        sf::Texture texture;
        if (!texture.loadFromFile(texturePath)) {
            std::cerr << "Erreur lors du chargement de " << texturePath << std::endl;
        }
        textureMap[name] = std::move(texture);
    }
}

void renderInfo(sf::RenderWindow& window, sf::Font& font, GameManager& game) {
    sf::Vector2u windowSize = window.getSize();
    auto windowWidth = static_cast<float>(windowSize.x);
    auto windowHeight = static_cast<float>(windowSize.y);

    sf::Text info(font);
    info.setCharacterSize(24);
    info.setFillColor(sf::Color::White);
    std::ostringstream stream;
    stream << "Location " << game.getCurrentLevelId() << " - " << game.getLevelName() << "\n"
           << "Farm power: " << game.getCurrentScore() << "/" << game.getTargetScore() << "\n"
           << "Cost: " << game.getCurrentCost() << "/" << game.getCurrentMaxCost();
    info.setString(stream.str());
    info.setPosition({windowWidth * 0.05f, windowHeight * 0.05f});
    window.draw(info);
}

void renderRetryText(sf::RenderWindow& window, sf::Font& font) {
    sf::Vector2u windowSize = window.getSize();
    auto windowWidth = static_cast<float>(windowSize.x);
    auto windowHeight = static_cast<float>(windowSize.y);

    sf::Text retry(font);
    retry.setCharacterSize(20);
    retry.setFillColor(sf::Color::White);
    retry.setString("Press R to restart.");
    retry.setPosition({windowWidth * 0.65f, windowHeight * 0.05f});
    window.draw(retry);
}

void renderCards(sf::RenderWindow& window, const std::vector<std::unique_ptr<Card>>& hand, const std::map<std::string, sf::Texture>& textureMap,std::vector<sf::Sprite>& sprites, float windowWidth, float windowHeight) {
    const float cardWidth = windowWidth / 10.f;
    const float cardHeight = windowHeight / 5.f;
    const float cardSpacing = windowWidth / 20.f;
    float scaleX = cardWidth / 75.f;
    float scaleY = cardHeight / 100.f;
    float totalWidth = hand.size() * cardWidth + (hand.size() - 1) * cardSpacing;
    float startX = (windowWidth - totalWidth) / 2.f;
    float bottom = windowHeight - cardHeight - 0.1f * cardHeight;

    sprites.clear();
    for (size_t i = 0; i < hand.size(); ++i) {
        const std::string& name = hand[i]->getName();
        sf::Sprite sprite(textureMap.at(name));
        sprite.setScale({scaleX, scaleY});
        sprite.setPosition({startX + i * (cardWidth + cardSpacing), bottom});
        sprites.push_back(sprite);
    }
    for (const auto& sprite : sprites) {
        window.draw(sprite);
    }
}

void renderScoreText(sf::RenderWindow& window, sf::Font& font, const std::vector<sf::Sprite>& sprites, int lastCard, const std::vector<int>& diceResults, int scoreDisplayTimer) {
    int totalFrames = diceResults.size()*30;
    int resultsToShow = (totalFrames - scoreDisplayTimer) / 30 + 1;
    resultsToShow = std::min(resultsToShow, static_cast<int>(diceResults.size()));
    int currentScore = 0;
    for (int i = 0; i < resultsToShow; ++i) {
        currentScore += diceResults[i];
    }
    if (scoreDisplayTimer > 0 && lastCard >= 0) {
        sf::Text cardScoreText = showCardScore(currentScore, font, 125.f);
        cardScoreText.setPosition({sprites[lastCard].getPosition().x, sprites[lastCard].getPosition().y - 60.f});
        window.draw(cardScoreText);
    }
}

void renderGameOver(sf::RenderWindow& window, sf::Font& font, float windowHeight) {
    sf::Text gameOverText(font);
    gameOverText.setString("          You no longer have enough crops to be profitable this season. \nYou now regret your decision to become a farmer.\nPress R to restart.");
    gameOverText.setCharacterSize(20);
    gameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
    gameOverText.setPosition({windowHeight * 0.5f, windowHeight * 0.5f});
    gameOverText.setStyle(sf::Text::Bold);
    window.clear();
    window.draw(gameOverText);
}

void renderNextLevel(sf::RenderWindow& window, sf::Font& font, float windowHeight, int NextLevelTimer) {
    if (NextLevelTimer > 0) {
        sf::Text nextLever(font);
        nextLever.setString("Moving to a bigger location !");
        nextLever.setCharacterSize(30);
        if (NextLevelTimer%15 == 0) nextLever.setFillColor(sf::Color(255, 255, 255, 0));
        else nextLever.setFillColor(sf::Color(255, 255, 255, 255));
        sf::FloatRect textRect = nextLever.getLocalBounds();
        // nextLever.setOrigin({textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f});
        nextLever.setPosition({windowHeight * 0.35f, windowHeight * 0.3f});
        nextLever.setStyle(sf::Text::Bold);
        window.draw(nextLever);
    }
}

void renderDiceRoll(sf::RenderWindow& window, sf::Font& font, float windowHeight, float windowWidth, const std::vector<int>& diceResults, int diceAnimationTime, AudioManager& audioManager) {
    if (diceResults.empty()) return;
    int totalFrames = diceResults.size()*30;
    int resultsToShow = (totalFrames - diceAnimationTime) / 30 + 1;
    resultsToShow = std::min(resultsToShow, static_cast<int>(diceResults.size()));
    if ((totalFrames - diceAnimationTime)%29 == 0 && resultsToShow < diceResults.size()) {
        audioManager.combo(resultsToShow);
    }
    sf::Text diceText(font);
    std::ostringstream oss;
    oss << "Crop Result: ";
    for (int i = 0; i < resultsToShow; ++i) {
        if (i > 0) oss << " ";
        oss << diceResults[i];
    }
    diceText.setString(oss.str());
    diceText.setCharacterSize(20);
    diceText.setFillColor(sf::Color::White);
    diceText.setPosition({windowWidth * 0.15f, windowHeight * 0.5f});
    window.draw(diceText);
}

