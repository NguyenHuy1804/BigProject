#include "SoundManager.h"

SoundManager::SoundManager()
    : startScreenSound(nullptr), flapSound(nullptr),
    passPipeSound(nullptr), gameOverSound(nullptr), backgroundMusic(nullptr) {
}

SoundManager::~SoundManager() {
    clean();
}

bool SoundManager::loadSounds() {
    flapSound = Mix_LoadWAV("Game_Sounds/flap.wav");
    passPipeSound = Mix_LoadWAV("Game_Sounds/point.wav");
    gameOverSound = Mix_LoadWAV("Game_Sounds/gameover.wav");

    startScreenSound = Mix_LoadWAV("Game_Sounds/startscreen_fantasy.wav");
    backgroundMusic = Mix_LoadMUS("Game_Sounds/space_chord.mp3");

    if (!startScreenSound) {
        std::cerr << "Error loading start screen sound: " << Mix_GetError() << std::endl;
    }

    if (!passPipeSound) {
        std::cerr << "Error loading point sound: " << Mix_GetError() << std::endl;
        return false;
    }

    if (!backgroundMusic) {
        std::cerr << "Error loading background music: " << Mix_GetError() << std::endl;
    }

    return true;
}

void SoundManager::playStartScreenSound() {
    if (startScreenSound) {
        Mix_PlayChannel(-1, startScreenSound, 0);
    }
    else {
        std::cerr << "Start screen sound not loaded!" << std::endl;
    }
}

void SoundManager::playFlapSound() {
    if (flapSound) {
        Mix_PlayChannel(-1, flapSound, 0);
    }
    else {
        std::cerr << "Flap sound not loaded!" << std::endl;
    }
}

void SoundManager::playPassPipeSound() {
    if (passPipeSound) {
        Mix_PlayChannel(-1, passPipeSound, 0);
    }
    else {
        std::cerr << "Pass Pipe sound not loaded!" << std::endl;
    }
}

void SoundManager::playGameOverSound() {
    if (gameOverSound) {
        Mix_PlayChannel(-1, gameOverSound, 0);
    }
    else {
        std::cerr << "Game Over sound not loaded!" << std::endl;
    }
}

void SoundManager::playBackgroundMusic() {
    if (backgroundMusic) {
        Mix_PlayMusic(backgroundMusic, -1); // -1 = loop mãi mãi
    }
    else {
        std::cerr << "Background music not loaded!" << std::endl;
    }
}

void SoundManager::stopBackgroundMusic() {
    Mix_HaltMusic();
}

void SoundManager::stopAllSounds() {
    Mix_HaltChannel(-1); // Dừng tất cả các kênh âm thanh
    Mix_HaltMusic();     // Dừng nhạc nền
}

void SoundManager::stopStartScreenSound() {
    // Tìm và dừng kênh đang phát startScreenSound
    int channels = Mix_AllocateChannels(-1);
    for (int i = 0; i < channels; i++) {
        if (Mix_GetChunk(i) == startScreenSound) {
            Mix_HaltChannel(i);
            break;
        }
    }
}

void SoundManager::clean() {
    if (startScreenSound) Mix_FreeChunk(startScreenSound);
    if (flapSound) Mix_FreeChunk(flapSound);
    if (passPipeSound) Mix_FreeChunk(passPipeSound);
    if (gameOverSound) Mix_FreeChunk(gameOverSound);
    if (backgroundMusic) Mix_FreeMusic(backgroundMusic);
}


