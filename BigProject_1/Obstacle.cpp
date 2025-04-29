#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle(SDL_Renderer* renderer, int pipeGapY, int gapHeight)
    : renderer(renderer), texture(nullptr), speed(2), movingUp(true) {

    // Kích thước chướng ngại vật
    rect.w = 40;
    rect.h = 40;

    // Vị trí xuất hiện (ngang với khoảng trống giữa 2 ống)
    rect.x = 800; // Bắt đầu từ bên phải màn hình

    // Giới hạn di chuyển (không chặn hoàn toàn lối vào pipe)
    minY = pipeGapY + 20;
    maxY = pipeGapY + gapHeight - 20 - rect.h;

    // Vị trí Y ban đầu (ngẫu nhiên trong phạm vi cho phép)
    rect.y = minY + (rand() % (maxY - minY));
}

Obstacle::~Obstacle() {
    if (texture) SDL_DestroyTexture(texture);
}

void Obstacle::update() {
    // Di chuyển sang trái
    rect.x -= 3;

    // Di chuyển lên xuống
    if (movingUp) {
        rect.y -= speed;
        if (rect.y <= minY) movingUp = false;
    }
    else {
        rect.y += speed;
        if (rect.y >= maxY) movingUp = true;
    }
}

void Obstacle::render() {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        std::cout << "Rendering obstacle at: " << rect.x << "," << rect.y << std::endl;
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        std::cout << "Rendering obstacle placeholder at: " << rect.x << "," << rect.y << std::endl;
    }
}

bool Obstacle::checkCollision(SDL_Rect rect) const {
    return SDL_HasIntersection(&this->rect, &rect);
}


bool Obstacle::loadTexture(const char* path) {
    if (texture) {
        SDL_DestroyTexture(texture);  // Giải phóng texture cũ nếu có
    }

    SDL_Surface* surface = IMG_Load(path);
    if (!surface) {
        std::cerr << "Failed to load obstacle texture: " << IMG_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}