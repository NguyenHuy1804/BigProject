#pragma once
#include <SDL.h>
#include "Bird.h"

class Pipe {
public:
    Pipe(SDL_Renderer* renderer, int x);
    void update();
    void render();
    bool collidesWith(Bird* bird);

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect topPipe, bottomPipe;
};
