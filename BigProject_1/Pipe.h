#pragma once
#include <SDL.h>
#include "Bird.h"

class Pipe {
public:

    bool isOffScreen() const {
        return topPipe.x + topPipe.w < 0;
    }

    Pipe(SDL_Renderer* renderer, int x);
    void update();
    void render();
    int getX() const; 
    int getWidth(); 
    bool collidesWith(Bird* bird);
    bool isPassed() const;  
    void setPassed(bool value);  
    int getGapY() const { return gapY; } // Thêm hàm này
    int getGapHeight() const { return gapHeight; } // Và/hoặc hàm này

private:
    int gapY;
    int gapHeight;
    int x;
    int width;
    bool passed;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect topPipe, bottomPipe;
};
