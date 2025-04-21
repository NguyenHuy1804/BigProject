#include "StartScreen.h"
#include "TextureManager.h"

StartScreen::StartScreen(SDL_Renderer* renderer) : renderer(renderer) {
    texture = TextureManager::LoadTexture("Game_Images/Game_screen.jpg", renderer);
    rect = { 0, 0, 800, 600 };
}

void StartScreen::render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
