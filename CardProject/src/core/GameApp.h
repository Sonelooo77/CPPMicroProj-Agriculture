//
// Created by Steve on 17/06/2025.
//

#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "CardFactory.h"
#include "LevelFactory.h"
#include "GameManager.h"
#include "AudioManager.h"

class GameApp {
public:
    GameApp();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    sf::Font font;
    sf::Texture backgroundTexture;
    std::map<std::string, sf::Texture> textureMap;
    std::vector<sf::Sprite> sprites;
    int lastCard = -1;
    int lastScore = 0;
    int scoreDisplayTimer = 0;
    int nextLevelTimer = 0;
    bool gameOver = false;

    std::vector<int> lastDiceDetails;

    CardFactory cardFactory;
    LevelFactory levelFactory;
    GameManager game;
    AudioManager note;
};
#endif //GAMEAPP_H
