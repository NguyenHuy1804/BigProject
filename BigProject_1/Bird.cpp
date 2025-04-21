#include "Bird.h"
#include <cmath>
#include "TextureManager.h"

Bird::Bird(SDL_Renderer* renderer) : renderer(renderer), velocity(0) {
    texture = TextureManager::LoadTexture("Game_Images/Nasa_craft.png", renderer);
    rect = { 100, 300, 50, 50 };
}

void Bird::update() {
    velocity += 0.5f;
    rect.y += static_cast<int>(velocity);

    if (rect.y > 600 - rect.h) {
        rect.y = 600 - rect.h;
    }
    rect.y = std::max(0, rect.y);
}

void Bird::render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Bird::flap() {
    velocity = -8.0f;
}

SDL_Rect Bird::getRect() {
    return rect;
}
