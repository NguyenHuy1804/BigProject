#pragma once
#include <SDL.h>
#include <SDL_image.h>  // Sửa từ SQL.h/SQL_image.h thành SDL.h/SDL_image.h

class Obstacle {
public:
    Obstacle(SDL_Renderer* renderer, int pipeGapY, int gapHeight);
    ~Obstacle();  // Sửa từ -Obstacle() thành ~Obstacle()

    void update();
    void render();
    bool checkCollision(SDL_Rect rect) const;
    bool loadTexture(const char* path);  // Chỉ giữ lại khai báo này
    SDL_Rect getRect() const { return rect; }  // Sửa SQL_Rect → SDL_Rect

private:
    SDL_Renderer* renderer;  // Sửa SQL_Renderer → SDL_Renderer
    SDL_Texture* texture;    // Sửa SQL_Texture → SDL_Texture
    SDL_Rect rect;           // Sửa SQL_Rect → SDL_Rect
    int speed;
    bool movingUp;
    int minY;  // Sửa từ minV → minY (cho rõ nghĩa)
    int maxY;  // Sửa từ maxV → maxY
};