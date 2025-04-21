#include "GameOverScreen.h"
#include "TextureManager.h"

GameOverScreen::GameOverScreen(SDL_Renderer* renderer) : renderer(renderer) {
    texture = TextureManager::LoadTexture("Game_Images/gameover.png", renderer);
    rect = { 0, 0, 800, 600 };
}

void GameOverScreen::render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
