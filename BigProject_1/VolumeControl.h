#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class VolumeControl {
public:
    VolumeControl(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~VolumeControl();

    void loadResources();
    void handleEvent(SDL_Event& e);
    void render();
    void toggleVisibility();
    bool isVisible() const;
    bool isGamePaused() const;
    SDL_Rect getMenuRect() const { return menuRect; }

private:
    SDL_Renderer* renderer;

    // Textures
    SDL_Texture* menuTexture;
    SDL_Texture* knobTexture;

    // Font
    TTF_Font* font;

    // Rects
    SDL_Rect menuRect;
    SDL_Rect barRect;
    SDL_Rect knobRect;

    // State
    bool visible;
    int volume;
    bool dragging;
    bool gamePaused;
};