#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Bird.h"
#include "Pipe.h"
#include "TextureManager.h"
#include "StartScreen.h"
#include "Background.h"
#include "GameOverScreen.h"
#include <vector>

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int width, int height);
    void run();
    void clean();

private:
    void handleEvents();
    void update();
    void render();
    void reset();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    enum State { START, PLAYING, GAMEOVER } gameState;

    Bird* bird;
    std::vector<Pipe*> pipes;
    int pipeSpawnTimer;

    StartScreen* startScreen;
    GameOverScreen* gameOverScreen;
    Background* background;
};
