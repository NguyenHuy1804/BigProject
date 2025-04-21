#include "Game.h"
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), gameState(START), bird(nullptr), pipeSpawnTimer(0), startScreen(nullptr), gameOverScreen(nullptr) {}

Game::~Game() {}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if (!IMG_Init(IMG_INIT_PNG)) return false;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!window || !renderer) return false;

    bird = new Bird(renderer);
    startScreen = new StartScreen(renderer);
    gameOverScreen = new GameOverScreen(renderer);
    background = new Background(renderer);
    return isRunning = true;

    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) < 0) {
        // handle error
    }

}

void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}

void Game::clean() {
    delete bird;
    for (auto pipe : pipes) delete pipe;
    delete startScreen;
    delete gameOverScreen;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) isRunning = false;
        if (gameState == START || gameState == GAMEOVER) {
            if (e.type == SDL_KEYDOWN) {
                if (gameState == START) gameState = PLAYING;
                else if (gameState == GAMEOVER) reset();
            }
        }
        if (gameState == PLAYING && e.type == SDL_KEYDOWN) {
            bird->flap();
        }
    }
}

void Game::update() {
    if (gameState == PLAYING) {
        background->update();
        bird->update();

        pipeSpawnTimer++;
        if (pipeSpawnTimer > 100) {
            pipes.push_back(new Pipe(renderer, 800));
            pipeSpawnTimer = 0;
        }

        for (auto pipe : pipes) {
            pipe->update();
        }

        for (auto pipe : pipes) {
            if (pipe->collidesWith(bird)) {
                gameState = GAMEOVER;
            }
        }

        // Kiểm tra nếu chim rơi xuống đất thì game over
        if (bird->getRect().y + bird->getRect().h >= 600) {
            gameState = GAMEOVER;
        }

        // Không kiểm tra chim bay lên cao quá màn hình
    }
}


void Game::render() {
    SDL_RenderClear(renderer);
    if (gameState == START) startScreen->render();
    else if (gameState == PLAYING) {
        background->render();
        bird->render();
        for (auto pipe : pipes) pipe->render();
    }
    else if (gameState == GAMEOVER) gameOverScreen->render();
    SDL_RenderPresent(renderer);
}

void Game::reset() {
    delete bird;
    for (auto pipe : pipes) delete pipe;
    pipes.clear();
    bird = new Bird(renderer);
    gameState = START;
}
    
