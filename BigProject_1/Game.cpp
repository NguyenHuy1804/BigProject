#include "Game.h"
#include "SoundManager.h"
#include <SDL_ttf.h>
#include <string>
#include <iostream>

extern SoundManager* soundManager;

Game::Game()
    : window(nullptr), renderer(nullptr), isRunning(false), gameState(START),
    bird(nullptr), pipeSpawnTimer(0), startScreen(nullptr),
    gameOverScreen(nullptr), background(nullptr), volumeControl(nullptr) {
}

Game::~Game() {}

bool Game::init(const char* title, int width, int height) {
    if (TTF_Init() == -1) { 
        std::cerr << "SDL_ttf could not initialize! Error: " << TTF_GetError() << std::endl;
        return false;
    }

    score = 0;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return false;
    if (!IMG_Init(IMG_INIT_PNG)) return false;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return false;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!window || !renderer) return false;

    bird = new Bird(renderer);
    startScreen = new StartScreen(renderer);
    gameOverScreen = new GameOverScreen(renderer);
    background = new Background(renderer);
    volumeControl = new VolumeControl(renderer, width, height);

    soundManager->playStartScreenSound();
    volumeControl->loadResources();

    return isRunning = true;
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
    delete background;
    delete volumeControl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) isRunning = false;

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            volumeControl->toggleVisibility();
        }
        volumeControl->handleEvent(e);

        if (volumeControl->isGamePaused()) continue;

        if (gameState == START || gameState == GAMEOVER) {
            if (e.type == SDL_KEYDOWN) {
                if (gameState == START) {
                    soundManager->stopStartScreenSound();
                    soundManager->stopAllSounds();
                    gameState = PLAYING;
                    soundManager->playBackgroundMusic();
                }
                else if (gameState == GAMEOVER) {
                    soundManager->stopAllSounds();
                    reset();
                    soundManager->playStartScreenSound();
                }
            }
        }
        if (gameState == PLAYING && e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE) {
                bird->flap();
                soundManager->playFlapSound();
            }
        }
    }
}

void Game::update() {
    if (volumeControl->isGamePaused()) return;

    if (gameState == PLAYING) {
        background->update();
        bird->update();

        pipeSpawnTimer++;
        if (pipeSpawnTimer > 100) {
            pipes.push_back(new Pipe(renderer, 800));
            pipeSpawnTimer = 0;
        }

        for (auto pipe : pipes) pipe->update();

        for (auto pipe : pipes) {
            if (pipe->collidesWith(bird)) {
                gameOver();
                break;
            }
        }

        if (bird->getRect().y + bird->getRect().h >= 600) {
            gameOver();
        }

        checkIfBirdPassesPipe();
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    if (gameState == START) {
        startScreen->render();
    }
    else if (gameState == PLAYING) {
        background->render();
        for (auto pipe : pipes) pipe->render();
        bird->render();
        renderScore();
    }
    else if (gameState == GAMEOVER) {
        gameOverScreen->render();
        renderScore();
    }

    volumeControl->render();

    if (volumeControl->isGamePaused()) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderFillRect(renderer, NULL);
    }

    SDL_RenderPresent(renderer);
}

void Game::reset() {
    delete bird;
    for (auto pipe : pipes) delete pipe;
    pipes.clear();
    bird = new Bird(renderer);
    score = 0;
    gameState = START;
}

void Game::gameOver() {
    gameState = GAMEOVER;
    soundManager->stopBackgroundMusic();
    soundManager->stopAllSounds();
    soundManager->playGameOverSound();
    std::cout << "Game Over! Final Score: " << score << std::endl;
}

void Game::checkIfBirdPassesPipe() {
    for (auto pipe : pipes) {
        if (!pipe->isPassed() && pipe->getX() + pipe->getWidth() < bird->getRect().x) {
            pipe->setPassed(true);
            score++;
            soundManager->playPassPipeSound();
        }
    }
}

void Game::renderScore() {
    static TTF_Font* font = TTF_OpenFont("Fonts/Pixeboy-z8XGD.ttf", 28);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color color = { 255, 255, 255, 255 };
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = { 10, 10, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}