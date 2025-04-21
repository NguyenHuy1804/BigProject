#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
    : flapSound(nullptr), passPipeSound(nullptr), gameOverSound(nullptr),
    startScreenMusic(nullptr), gameMusic(nullptr) {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

SoundManager::~SoundManager() {
    clean();  // Gọi hàm clean để giải phóng
}

bool SoundManager::loadSounds() {
    flapSound = Mix_LoadWAV("Game_Sounds/flap.wav");
    passPipeSound = Mix_LoadWAV("Game_Sounds/point.wav");
    gameOverSound = Mix_LoadWAV("Game_Sounds/gameover.wav");

    startScreenMusic = Mix_LoadMUS("Game_Sounds/startscreen.mp3");


    if (!flapSound){
        std::cerr << "Error loading flap sound: " << Mix_GetError() << std::endl;
        return false;
    }
    

    return true;
}

void SoundManager::playFlapSound() {
    Mix_PlayChannel(-1, flapSound, 0);
}

void SoundManager::playPassPipeSound() {
    Mix_PlayChannel(-1, passPipeSound, 0);
}

void SoundManager::playGameOverSound() {
    Mix_PlayChannel(-1, gameOverSound, 0);
}

void SoundManager::playStartScreenMusic() {
    Mix_PlayMusic(startScreenMusic, -1);  // Loop forever
}

void SoundManager::stopMusic() {
    Mix_HaltMusic();
}

void SoundManager::clean() {
    if (flapSound) {
        Mix_FreeChunk(flapSound);
        flapSound = nullptr;
    }

    if (passPipeSound) {
        Mix_FreeChunk(passPipeSound);
        passPipeSound = nullptr;
    }

    if (gameOverSound) {
        Mix_FreeChunk(gameOverSound);
        gameOverSound = nullptr;
    }

    if (startScreenMusic) {
        Mix_FreeMusic(startScreenMusic);
        startScreenMusic = nullptr;
    }

    Mix_CloseAudio();
}

