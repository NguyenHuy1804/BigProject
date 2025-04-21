//#include "Snake.h"
//
//Snake::Snake(SDL_Renderer* renderer) : renderer(renderer) {
//    SDL_Surface* surface = IMG_Load("Game_Images/Felix_Char.png");
//    texture = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//    SDL_Rect head = { 100, 100, 20, 20 };
//    body.push_back(head);
//}
//
//void Snake::handleEvent(SDL_Event& event) {
//    if (event.type == SDL_KEYDOWN) {
//        switch (event.key.keysym.sym) {
//        case SDLK_w: if (dy == 0) { dx = 0; dy = -20; } break; // W -> Up
//        case SDLK_s: if (dy == 0) { dx = 0; dy = 20; } break; // S -> Down
//        case SDLK_a: if (dx == 0) { dx = -20; dy = 0; } break; // A -> Left
//        case SDLK_d: if (dx == 0) { dx = 20; dy = 0; } break; // D -> Right
//        }
//    }
//}
//
//void Snake::move() {
//    for (int i = body.size() - 1; i > 0; i--)
//        body[i] = body[i - 1];
//    body[0].x += dx;
//    body[0].y += dy;
//}
//
//void Snake::grow() {
//    SDL_Rect newSegment = body.back();
//    body.push_back(newSegment);
//}
//
//void Snake::render() {
//    for (auto& segment : body)
//        SDL_RenderCopy(renderer, texture, NULL, &segment);
//}
//
//SDL_Rect Snake::getHeadRect() {
//    return body[0];
//}
//
//bool Snake::checkCollision(SDL_Rect food) {
//    return SDL_HasIntersection(&body[0], &food);
//}
//
//bool Snake::checkSelfCollision() {
//    SDL_Rect head = body[0];
//    for (size_t i = 1; i < body.size(); ++i) {
//        if (SDL_HasIntersection(&head, &body[i])) {
//            return true;
//        }
//    }
//    return false;
//}
