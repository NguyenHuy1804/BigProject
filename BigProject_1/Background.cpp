#include "Background.h"
#include <SDL_image.h>
#include <iostream>

Background::Background(SDL_Renderer* renderer) {
    this->renderer = renderer;
    scrollSpeed = 1.0f;

    SDL_Surface* surface = IMG_Load("Game_Images/background_universe.jpg");
    if (!surface) {
        std::cout << "Failed to load background image: " << IMG_GetError() << std::endl;
        texture = nullptr;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cout << "Failed to create background texture: " << SDL_GetError() << std::endl;
    }


    rect1 = { 0, 0, 800, 600 };
    rect2 = { 800, 0, 800, 600 };
}

Background::~Background() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Background::update() {
    rect1.x -= static_cast<int>(scrollSpeed);
    rect2.x -= static_cast<int>(scrollSpeed);

    if (rect1.x + rect1.w <= 0) {
        rect1.x = rect2.x + rect2.w;
    }

    if (rect2.x + rect2.w <= 0) {
        rect2.x = rect1.x + rect1.w;
    }
}

void Background::render() {
    SDL_RenderCopy(renderer, texture, NULL, &rect1);
    SDL_RenderCopy(renderer, texture, NULL, &rect2);
}

