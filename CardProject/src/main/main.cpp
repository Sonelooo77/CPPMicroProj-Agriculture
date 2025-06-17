#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include "CardFactory.h"
#include "GameManager.h"
#include "LevelFactory.h"
#include "Renderer.h"
#include "AudioManager.h"


int main() {
    CardFactory cardFactory("resources/cardsdefinition.xml");
    LevelFactory levelFactory("resources/levelsdefinition.xml");

    GameManager game;
    game.setCardFactory(&cardFactory);
    game.setLevelFactory(&levelFactory);
    game.startLevel();

    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Jeu de Cartes");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Font font;
    if (!font.openFromFile("resources/assets/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return -1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("resources/assets/background.png")) {
        std::cerr << "Erreur lors du chargement du Background" << std::endl;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    std::map<std::string, sf::Texture> textureMap;
    loadTextures(cardFactory.getAvailableCards(), textureMap);

    std::vector<sf::Sprite> sprites;
    int lastCard = -1;
    int lastScore = 0;
    int scoreDisplayTimer = 0;
    int NextLevelTimer = 0;
    int diceAnimationTime = 0;
    std::vector<int> lastDiceDetails;


    AudioManager notedo("resources/sounds/do.wav");
    notedo.play();

    while (window.isOpen()) {


        window.clear();
        window.draw(backgroundSprite);

        renderInfo(window, font, game);
        renderRetryText(window, font);

        const auto& hand = game.getPlayerHand();
        sf::Vector2u windowSize = window.getSize();
        auto windowWidth = static_cast<float>(windowSize.x);
        auto windowHeight = static_cast<float>(windowSize.y);
        renderCards(window,hand, textureMap, sprites, windowWidth, windowHeight);

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && scoreDisplayTimer == 0) {
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for (size_t i = 0; i < sprites.size(); ++i) {
                        if (sprites[i].getGlobalBounds().contains(mousePos)) {
                            game.playCard(*hand[i]);
                            lastDiceDetails = hand[i]->getLastDiceDetails();
                            scoreDisplayTimer = 250;
                            notedo.combo(0);
                            game.removeCardFromHand(i);
                            lastCard = static_cast<int>(i);
                            break;
                        }
                    }
                }
            }
        }

        if (scoreDisplayTimer>0) {
            scoreDisplayTimer--;
            renderDiceRoll(window, font, windowHeight, windowWidth, lastDiceDetails,scoreDisplayTimer, notedo);
            renderScoreText(window, font, sprites, lastCard, lastDiceDetails, scoreDisplayTimer);
        }
        if (NextLevelTimer > 0) {
            renderNextLevel(window, font, windowHeight, NextLevelTimer);
            --NextLevelTimer;
        }

        if (game.isGameWon()) {
            std::cout << "Level cleared!" << std::endl;
            if (!game.isGameCompleted()) {
                game.nextLevel();
                NextLevelTimer = 60;
                game.startLevel();
            } else {
                std::cout << "Game won!" << std::endl;
                break;
            }
        } else if (game.isGameLost()) {
            renderGameOver(window, font, windowHeight);
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
