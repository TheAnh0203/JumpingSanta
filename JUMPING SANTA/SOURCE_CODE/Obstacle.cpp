#include "Obstacle.h"

Obstacle::Obstacle()
{
	posX = 0;
	posY = 0;

	oWidth = 0;
	oHeight = 0;

	posX = rand() % (SCREEN_WIDTH + OBSTACLE_POSITION_RANGE) + SCREEN_WIDTH;
	posY = 385;

	ObstacleTexture = nullptr;
}

Obstacle::~Obstacle()
{
	posX = 0;
	posY = 0;

	oWidth = 0;
	oHeight = 0;

	if (ObstacleTexture != nullptr)
	{
		ObstacleTexture = nullptr;
	}
}

void Obstacle::LoadFile(int frame, SDL_Renderer* gRenderer)
{
	std::string path;
	switch (frame)
	{
	case 1:
		path = CRYSTAL_OBSTACLE;
		break;
	case 2:
		path = STONE_OBSTACLE;
		break;
	default:
		break;
	}

	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	if (tempSurface == nullptr)
	{
		std::cout << "Can not load image." << std::endl;
	}
	else
	{
		ObstacleTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);

		if (ObstacleTexture == nullptr)
		{
			std::cout << "Can not create texture from surface." << std::endl;
		}
		else
		{
			oWidth = tempSurface->w;
			oHeight = tempSurface->h;
		}
		SDL_FreeSurface(tempSurface);
	}
}

void Obstacle::Move(const int& acceleration)
{
	posX -= (OBSTACLE_SPEED + acceleration);
	if (posX < OBSTACLE_LIMIT_X)
	{
		posX = rand() % (SCREEN_WIDTH + OBSTACLE_POSITION_RANGE) + SCREEN_WIDTH;
	}
}

void Obstacle::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = { posX, posY, oWidth, oHeight };
	if (currentClip != nullptr)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, ObstacleTexture, currentClip, &renderSpace);
}

int Obstacle::GetSpeed(const int& acceleration)
{
	return 5 + acceleration;
}

