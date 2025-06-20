//
// Created by Steve on 17/06/2025.
//

#include "AudioManager.h"
#include <SFML/Audio.hpp>

AudioManager::AudioManager()
    : buffer(), audio(buffer)
{
}

void AudioManager::play(const std::string& filename) {
    buffer= sf::SoundBuffer(filename);
    audio = sf::Sound(buffer);
    audio.play();
}

void AudioManager::combo(int i) {
    switch (i%4) {
        case 0:
            if (buffer.loadFromFile("resources/sounds/do.wav")) {
                audio.setBuffer(buffer);
                audio.play();
            }
            break;
        case 1:
            if (buffer.loadFromFile("resources/sounds/re.wav")) {
                audio.setBuffer(buffer);
                audio.play();
            }
            break;
        case 2:
            if (buffer.loadFromFile("resources/sounds/mi.wav")) {
                audio.setBuffer(buffer);
                audio.play();
            }
            break;
        case 3:
            if (buffer.loadFromFile("resources/sounds/fa.wav")) {
                audio.setBuffer(buffer);
                audio.play();
            }
            break;
        default: break;
    }
}

sf::Sound::Status AudioManager::getStatus() const {
    return audio.getStatus();
}



