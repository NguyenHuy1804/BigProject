#include "VolumeControl.h"
#include <SDL_mixer.h>
#include <iostream>

VolumeControl::VolumeControl(SDL_Renderer* renderer, int screenWidth, int screenHeight)
    : renderer(renderer), menuTexture(nullptr), knobTexture(nullptr), font(nullptr),
    visible(false), volume(50), dragging(false), gamePaused(false) {

    
    menuRect = {
        (screenWidth - 500) / 2,
        (screenHeight - 300) / 2,
        500,
        300,
    };

    
    barRect = {
        menuRect.x + 100,
        menuRect.y + 200,
        300,
        30
    };

   
    knobRect = {
        barRect.x + (volume * barRect.w / 100) - 10,
        barRect.y - 5,
        20,
        40
    };
}

VolumeControl::~VolumeControl() {
    if (menuTexture) SDL_DestroyTexture(menuTexture);
    if (knobTexture) SDL_DestroyTexture(knobTexture);
    if (font) TTF_CloseFont(font);
}

void VolumeControl::loadResources() {
    
    SDL_Surface* surface = IMG_Load("Game_Images/Menu_Setting_1.png");
    if (surface) {
        menuTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    
    surface = IMG_Load("Game_Images/Volume_Button.png");
    if (surface) {
        knobTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

  
    font = TTF_OpenFont("Fonts/Pixeboy-z8XGD.ttf", 36);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
}

void VolumeControl::handleEvent(SDL_Event& e) {
    if (!visible) return;

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x >= knobRect.x && x <= knobRect.x + knobRect.w &&
            y >= knobRect.y && y <= knobRect.y + knobRect.h) {
            dragging = true;
        }
        else if (x >= barRect.x && x <= barRect.x + barRect.w &&
            y >= barRect.y && y <= barRect.y + barRect.h) {
            volume = ((x - barRect.x) * 100) / barRect.w;
            knobRect.x = barRect.x + (volume * barRect.w / 100) - 10;
            dragging = true;
            Mix_Volume(-1, volume);
            Mix_VolumeMusic(volume);
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP) {
        dragging = false;
    }
    else if (e.type == SDL_MOUSEMOTION && dragging) {
        int x = e.motion.x;
        if (x < barRect.x) x = barRect.x;
        if (x > barRect.x + barRect.w) x = barRect.x + barRect.w;

        volume = ((x - barRect.x) * 100) / barRect.w;
        knobRect.x = barRect.x + (volume * barRect.w / 100) - 10;

        Mix_Volume(-1, volume);
        Mix_VolumeMusic(volume);
    }
}

void VolumeControl::render() {
    if (!visible) return;

    if (menuTexture) {
        SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);
    }
    else {

        SDL_SetRenderDrawColor(renderer, 50, 50, 80, 255);
        SDL_RenderFillRect(renderer, &menuRect);
    }

   
    SDL_SetRenderDrawColor(renderer, 100, 100, 150, 255);
    SDL_RenderFillRect(renderer, &barRect);


    if (knobTexture) {
        SDL_RenderCopy(renderer, knobTexture, NULL, &knobRect);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
        SDL_RenderFillRect(renderer, &knobRect);
    }


    if (font) {
        SDL_Color white = { 255, 255, 255, 255 };
        SDL_Surface* surface = TTF_RenderText_Solid(font, "VOLUME BAR", white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect titleRect = {
            menuRect.x + (menuRect.w - surface->w) / 2,
            menuRect.y + 50,
            surface->w,
            surface->h
        };

        SDL_RenderCopy(renderer, texture, NULL, &titleRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}


void VolumeControl::toggleVisibility() {
    visible = !visible;
    gamePaused = visible;
}

bool VolumeControl::isVisible() const {
    return visible;
}
bool VolumeControl::isGamePaused() const {
    return gamePaused;
}