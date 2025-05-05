#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Game.h"
#include "SoundManager.h"
#include <iostream>

SoundManager* soundManager = new SoundManager();


int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cout << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        return -1;
    }

    soundManager = new SoundManager();
    if (!soundManager->loadSounds()) {
        std::cout << "Failed to load sound effects." << std::endl;
        return -1;
    }

    Game game;
    if (!game.init("Space Rush", 800, 600)) {
        return -1;
    }

    game.run();
    game.clean();

    if (soundManager) {
        soundManager->clean();
        delete soundManager;
        soundManager = nullptr;
    }

    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
