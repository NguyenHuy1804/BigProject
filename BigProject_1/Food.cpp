//#include "Food.h"
//#include <cstdlib>
//#include <ctime>
//#include <SDL_image.h>
//#include <iostream>
//
//Food::Food(SDL_Renderer* renderer) : renderer(renderer) {
//    SDL_Surface* surface = IMG_Load("Game_Images/Felix_Hammer.png");
//
//    if (!surface) {
//        std::cerr << "Error loading image: " << IMG_GetError() << std::endl;
//        return;
//    }
//
//    texture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//
//    if (!texture) {
//        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
//        return;
//    }
//
//    srand(static_cast<unsigned>(time(0)));
//    respawn();
//}
//
//void Food::respawn() {
//    rect.w = rect.h = 30;
//    rect.x = (rand() % 40) * 20;
//    rect.y = (rand() % 30) * 20;
//}
//
//void Food::render() {
//    if (texture) {
//        SDL_RenderCopy(renderer, texture, NULL, &rect);
//    }
//    else {
//        std::cerr << "Texture not initialized!" << std::endl;
//    }
//}
//
//SDL_Rect Food::getRect() {
//    return rect;
//}
