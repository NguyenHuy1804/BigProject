#pragma once
#include "Bird.h"
#include "Pipe.h"
#include "StartScreen.h"
#include "GameOverScreen.h"
#include "Background.h"
#include "VolumeControl.h"
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
    void gameOver();
    void checkIfBirdPassesPipe();
    void renderScore();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    enum GameState { START, PLAYING, GAMEOVER } gameState;

    Bird* bird;
    std::vector<Pipe*> pipes;
    int pipeSpawnTimer;
    int score;

    StartScreen* startScreen;
    GameOverScreen* gameOverScreen;
    Background* background;
    VolumeControl* volumeControl;
};