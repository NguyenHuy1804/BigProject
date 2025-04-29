#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <iostream>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    bool loadSounds();

    void playStartScreenSound();
    void playFlapSound();
    void playPassPipeSound();
    void playGameOverSound();
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void stopAllSounds();
    void stopStartScreenSound();

    void clean();

private:
    Mix_Chunk* startScreenSound;
    Mix_Chunk* flapSound;
    Mix_Chunk* passPipeSound;
    Mix_Chunk* gameOverSound;
    Mix_Music* backgroundMusic;
};

#endif
