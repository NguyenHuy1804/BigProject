//#include "Game.h"
//#include "SoundManager.h"
//
//SoundManager soundManager;
//
//
//int main(int argc, char* argv[]) {
//    Game game;
//    if (!game.init("Flappy Bird", 800, 600)) return -1;
//    game.run();
//    game.clean();
//    return 0;
//
//}
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Game.h"
#include "SoundManager.h"
#include <iostream>

// Khai báo biến âm thanh toàn cục
SoundManager* soundManager = nullptr;


int main(int argc, char* argv[]) {
    // Khởi tạo SDL

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Khởi tạo SDL_image
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        std::cout << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        return -1;
    }

    // Khởi tạo SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! Mix_Error: " << Mix_GetError() << std::endl;
        return -1;
    }

    // Tạo và tải âm thanh
    soundManager = new SoundManager();
    if (!soundManager->loadSounds()) {
        std::cout << "Failed to load sound effects." << std::endl;
        return -1;
    }

    // Khởi tạo game
    Game game;
    if (!game.init("Flappy Bird", 800, 600)) {
        return -1;
    }

    game.run();
    game.clean();

    // Giải phóng âm thanh
    if (soundManager) {
        soundManager->clean();
        delete soundManager;
        soundManager = nullptr;
    }

    // Dọn dẹp SDL
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
