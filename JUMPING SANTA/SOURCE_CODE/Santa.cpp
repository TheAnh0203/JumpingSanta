#include "Santa.h"

Santa::Santa()
{
    posX = POSX_SANTA;
    posY = GROUND;

    status = 0;
}

bool Santa::OnGround()
{
    return posY == GROUND;
}

void Santa::HandleEvent(SDL_Event& event, Mix_Chunk* gJump)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if ((event.key.keysym.sym) == SDLK_UP)
        {
            if (OnGround())
            {
                Mix_PlayChannel(-1, gJump, 0);
                status = JUMP;
            }
        }
    }
}

void Santa::Move()
{
    if (status == JUMP && posY >= MAX_JUMP_HEIGHT)
    {
        posY -= JUMP_SPEED;
    }
    if (posY <= MAX_JUMP_HEIGHT)
    {
        status = FALL;
    }
    if (status == FALL && posY < GROUND)
    {
        posY += FALL_SPEED;
    }
}

void Santa::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, BaseObject gSantaTexture)
{
    gSantaTexture.Render(posX, posY, gRenderer, currentClip);
}