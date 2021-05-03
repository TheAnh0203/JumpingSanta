#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "BaseObject.h"

#define OBSTACLE_POSITION_RANGE 250
#define OBSTACLE1_RANGE 100
#define OBSTACLE2_RANGE 350

#define OBSTACLE_SPEED 5
#define OBSTACLE_LIMIT_X -110

class Obstacle
{
private:
    int posX, posY;
    int oWidth, oHeight;
    SDL_Texture* ObstacleTexture;

public:
    Obstacle();
    ~Obstacle();

    void LoadFile(int frame, SDL_Renderer* gRenderer);

    void Move(const int& acceleration);

    void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

    int GetSpeed(const int& acceleration);

    int GetPosX() const { return posX; }
    int GetPosY() const { return posY; }

    int GetWidth() const { return oWidth; }
    int GetHeight() const { return oHeight; }
};
#endif // !OBSTACLE_H