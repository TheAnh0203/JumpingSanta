#ifndef SANTA_H
#define SANTA_H

#include "BaseObject.h"

#define RUN	0
#define JUMP 1
#define FALL 2

#define MAX_JUMP_HEIGHT 210 

class Santa
{
private:
    int posX, posY;
    int status;

public:
    static const int JUMP_SPEED = 8;
    static const int FALL_SPEED = 8;

    Santa();

    bool OnGround();

    void HandleEvent(SDL_Event& e, Mix_Chunk* gJump);

    void Move();

    void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, BaseObject gCharacterTexture);

    int GetPosX() const { return posX; }
    int GetPosY() const { return posY; }
};

#endif // !SANTA_H