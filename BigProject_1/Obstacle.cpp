//#include "Obstacle.h"
//#include <cmath>
//#include <iostream>
//
//Obstacle::Obstacle(SDL_Renderer* renderer) : renderer(renderer) {
//    SDL_Surface* surface = IMG_Load("Game_Images/Ralph.jpg");
//    texture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//    rect.w = rect.h = 20;
//    rect.x = 0;
//    rect.y = 0;
//}
//
//void Obstacle::moveTowards(SDL_Rect target) {
//    int dx = target.x - rect.x;
//    int dy = target.y - rect.y;
//
//    if (abs(dx) > abs(dy)) {
//        rect.x += (dx > 0) ? 20 : -20;
//    }
//    else if (dy != 0) {
//        rect.y += (dy > 0) ? 20 : -20;
//    }
//}
//
//void Obstacle::render() {
//    SDL_RenderCopy(renderer, texture, NULL, &rect);
//}
//
//SDL_Rect Obstacle::getRect() {
//    return rect;
//}
