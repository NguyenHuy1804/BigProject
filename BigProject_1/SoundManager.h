#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    bool loadSounds();  // Load all necessary sounds

    void playFlapSound();
    void playPassPipeSound();
    void playGameOverSound();
    void playStartScreenMusic();
    void playGameMusic();
    void stopMusic();
    void clean();
private:
    Mix_Chunk* flapSound;
    Mix_Chunk* passPipeSound;
    Mix_Chunk* gameOverSound;

    Mix_Music* startScreenMusic;
    Mix_Music* gameMusic;
};

#endif
    