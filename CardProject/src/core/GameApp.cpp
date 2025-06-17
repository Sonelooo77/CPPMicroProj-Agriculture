#include "GameApp.h"
#include "Renderer.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AudioManager.h"
#include "CardFactory.h"
#include "LevelFactory.h"
#include "GameManager.h"


GameApp::GameApp() : window(sf::VideoMode({1000, 800}), "Jeu de Cartes"),
                     cardFactory("resources/cardsdefinition.xml"),
                     levelFactory("resources/levelsdefinition.xml")
{
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    if (!font.openFromFile("resources/assets/arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("resources/assets/background.png")) {
        std::cerr << "Erreur lors du chargement du Background" << std::endl;
    }



    loadTextures(cardFactory.getAvailableCards(), textureMap);

    game.setCardFactory(&cardFactory);
    game.setLevelFactory(&levelFactory);
    game.startLevel();
}

void GameApp::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GameApp::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && scoreDisplayTimer == 0) {
            if (event->is<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                const auto& hand = game.getPlayerHand();
                for (size_t i = 0; i < sprites.size(); ++i) {
                    if (sprites[i].getGlobalBounds().contains(mousePos)) {
                        game.playCard(*hand[i]);
                        lastDiceDetails = hand[i]->getLastDiceDetails();
                        scoreDisplayTimer = 30 * lastDiceDetails.size();
                        note.combo(0);
                        game.removeCardFromHand(i);
                        lastCard = static_cast<int>(i);
                        break;
                    }
                }
            }
        }
    }
}

void GameApp::update() {
    if (scoreDisplayTimer > 0) {
        scoreDisplayTimer--;
    }
    if (nextLevelTimer > 0) {
        --nextLevelTimer;
    }
    if (game.isGameWon()) {
        std::cout << "Level cleared!" << std::endl;
        if (!game.isGameCompleted()) {
            game.nextLevel();
            nextLevelTimer = 60;
            game.startLevel();
        } else {
            std::cout << "Game won!" << std::endl;
            window.close();
        }
    } else if (game.isGameLost()) {
        gameOver = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        game.restart();
        game.startLevel();
    }
}

void GameApp::render() {
    window.clear();
    sf::Sprite backgroundSprite(backgroundTexture);
    window.draw(backgroundSprite);
    if (gameOver) {
        renderGameOver(window, font, window.getSize().y);
    }
    else {
        renderInfo(window, font, game);
        renderRetryText(window, font);

        const auto& hand = game.getPlayerHand();
        sf::Vector2u windowSize = window.getSize();
        auto windowWidth = static_cast<float>(windowSize.x);
        auto windowHeight = static_cast<float>(windowSize.y);
        renderCards(window, hand, textureMap, sprites, windowWidth, windowHeight);

        if (scoreDisplayTimer > 0) {
            renderDiceRoll(window, font, windowHeight, windowWidth, lastDiceDetails, scoreDisplayTimer, note);
            renderScoreText(window, font, sprites, lastCard, lastDiceDetails, scoreDisplayTimer);
        }
        if (nextLevelTimer > 0) {
            renderNextLevel(window, font, windowHeight, nextLevelTimer);
        }
        if (game.isGameLost()) {
            renderGameOver(window, font, windowHeight);
        }
    }
    window.display();
}

