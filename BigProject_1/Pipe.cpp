#include "Pipe.h"
#include "TextureManager.h"
#include <cstdlib>
#include <algorithm>


bool Pipe::isPassed() const {
    return passed;
}

void Pipe::setPassed(bool value) {
    passed = value;
}

Pipe::Pipe(SDL_Renderer* renderer, int x) : renderer(renderer) {
    texture = TextureManager::LoadTexture("Game_Images/Pipe_white.png", renderer);
    int height = rand() % 200 + 100;
    topPipe = { x, 0, 80, height };
    bottomPipe = { x, height + 150, 80, 600 - (height + 150) };
}

void Pipe::update() {
    topPipe.x -= 4;
    bottomPipe.x -= 4;
}

void Pipe::render() {
    SDL_RenderCopyEx(renderer, texture, nullptr, &topPipe, 0.0, nullptr, SDL_FLIP_VERTICAL);
    SDL_RenderCopy(renderer, texture, nullptr, &bottomPipe);
}

bool Pipe::collidesWith(Bird* bird) {
    SDL_Rect birdRect = bird->getRect();
    return SDL_HasIntersection(&birdRect, &topPipe) || SDL_HasIntersection(&birdRect, &bottomPipe);
}

int Pipe::getX() const {
    return topPipe.x;
}

int Pipe::getWidth() {
    return topPipe.w;
}
