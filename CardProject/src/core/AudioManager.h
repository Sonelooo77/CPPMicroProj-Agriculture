//
// Created by Steve on 17/06/2025.
//

#ifndef SOUND_H
#define SOUND_H
#include <SFML/Audio.hpp>
#include <string>

class AudioManager {
public:
    explicit AudioManager();
    void play(const std::string &filename);
    void combo(int i);
    sf::Sound::Status getStatus() const;
private:
    sf::SoundBuffer buffer;
    sf::Sound audio;
};

#endif //SOUND_H
